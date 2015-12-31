#include "DocumentCommon.h"

#include "simdyn.h"

#include <QStatusBar>
#include <QApplication>
#include <QColor>
#include <QColorDialog>

#include <Aspect_DisplayConnection.hxx>
#include <AIS_InteractiveObject.hxx>
#include <Graphic3d_NameOfMaterial.hxx>
#include <OpenGl_GraphicDriver.hxx>
#include <TCollection_AsciiString.hxx>

Handle(V3d_Viewer) DocumentCommon::Viewer(const Standard_ExtString theName,
	const Standard_CString theDomain,
	const Standard_Real theViewSize,
	const V3d_TypeOfOrientation theViewProj,
	const Standard_Boolean theComputedMode,
	const Standard_Boolean theDefaultComputedMode)
{
	static Handle(OpenGl_GraphicDriver) aGraphicDriver;

	if (aGraphicDriver.IsNull())
	{
		Handle(Aspect_DisplayConnection) aDisplayConnection;
#if !defined(_WIN32) && !defined(__WIN32__) && (!defined(__APPLE__) || defined(MACOSX_USE_GLX))
		aDisplayConnection = new Aspect_DisplayConnection(qgetenv("DISPLAY").constData());
#endif
		aGraphicDriver = new OpenGl_GraphicDriver(aDisplayConnection);
	}

	return new V3d_Viewer(aGraphicDriver,
		theName,
		theDomain,
		theViewSize,
		theViewProj,
		Quantity_NOC_GRAY30,
		V3d_ZBUFFER,
		V3d_GOURAUD,
		V3d_WAIT,
		theComputedMode,
		theDefaultComputedMode,
		V3d_TEX_NONE);
}

DocumentCommon::DocumentCommon(const int theIndex, SimDyn* app)
	: QObject(app)
	, myApp(app)
	, myIndex(theIndex)
	, myNbViews(0)
{
	TCollection_ExtendedString a3DName("Visu3D");
	myViewer = Viewer(a3DName.ToExtString(), "", 1000.0, V3d_XposYnegZpos, Standard_True, Standard_True);
	myViewer->SetDefaultLights();
	myViewer->SetLightOn();

	myContext = new AIS_InteractiveContext(myViewer);
}

DocumentCommon::~DocumentCommon()
{
}

Handle(AIS_InteractiveContext) DocumentCommon::getContext()
{
	return myContext;
}

MDIWindow* DocumentCommon::createNewMDIWindow()
{
	QMdiArea* ws = myApp->getWorkspace();
	return new MDIWindow(this, ws, 0);
}

void DocumentCommon::onCreateNewView()
{
	QMdiArea* ws = myApp->getWorkspace();
	MDIWindow* w = createNewMDIWindow();

	if (!w)
		return;

	ws->addSubWindow(w);
	myViews.append(w);

// 	connect(w, SIGNAL(selectionChanged()),
// 		this, SIGNAL(selectionChanged()));
// 	connect(w, SIGNAL(message(const QString&, int)),
// 		myApp->statusBar(), SLOT(showMessage(const QString&, int)));
// 	connect(w, SIGNAL(sendCloseView(MDIWindow*)),
// 		this, SLOT(onCloseView(MDIWindow*)));

	QString aName;
	w->setWindowTitle(aName.sprintf("Document %d:%d", myIndex, ++myNbViews));

	if (ws->subWindowList().isEmpty())
	{
		// Due to strange Qt4.2.3 feature the child window icon is not drawn
		// in the main menu if showMaximized() is called for a non-visible child window
		// Therefore calling show() first...
		w->show();
		w->showMaximized();
	}
	else
		w->show();

	w->setFocus();

	//getApplication()->onSelectionChanged();
}