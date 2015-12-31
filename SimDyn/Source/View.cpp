#include "View.h"
#include "simdyn.h"

#include <QApplication>
#include <QPainter>
#include <QMenu>
#include <QColorDialog>
#include <QCursor>
#include <QFileInfo>
#include <QFileDialog>
#include <QMouseEvent>
#include <QRubberBand>
#include <QMdiSubWindow>
#include <QStyleFactory>

#include <Visual3d_View.hxx>
#include <Graphic3d_ExportFormat.hxx>
#include <Graphic3d_GraphicDriver.hxx>
#include <Graphic3d_TextureEnv.hxx>

#if defined(_WIN32) || defined(__WIN32__)
#include <WNT_Window.hxx>
#elif defined(__APPLE__) && !defined(MACOSX_USE_GLX)
#include <Cocoa_Window.hxx>
#else
#include <QX11Info>
#include <GL/glx.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xmu/StdCmap.h>
#include <X11/Xlib.h>
#include <Xw_Window.hxx>
#include <QColormap>
#endif

#include <Aspect_DisplayConnection.hxx>

// the key for multi selection :
#define MULTISELECTIONKEY Qt::ShiftModifier

// the key for shortcut ( use to activate dynamic rotation, panning )
#define CASCADESHORTCUTKEY Qt::ControlModifier

// for elastic bean selection
#define ValZWMin 1

static QCursor* defCursor = NULL;
static QCursor* handCursor = NULL;
static QCursor* panCursor = NULL;
static QCursor* globPanCursor = NULL;
static QCursor* zoomCursor = NULL;
static QCursor* rotCursor = NULL;

View::View(Handle(AIS_InteractiveContext) theContext, QWidget* parent)
	: QWidget(parent)
	, myIsRaytracing(false)
	, myIsShadowsEnabled(true)
	, myIsReflectionsEnabled(false)
	, myIsAntialiasingEnabled(false)
	, myViewActions(0)
	, myRaytraceActions(0)
	, myBackMenu(NULL)
{
	myFirst = true;
	myContext = theContext;

	myXmin = 0;
	myYmin = 0;
	myXmax = 0;
	myYmax = 0;
	myCurZoom = 0;
	myRectBand = 0;

	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);

	myCurrentMode = CurAction3d_Nothing;
	myHlrModeIsOn = Standard_False;
	setMouseTracking(true);

	///*initViewActions*/();
	initCursors();

	setBackgroundRole(QPalette::NoRole);//NoBackground );
	// set focus policy to threat QContextMenuEvent from keyboard  
	setFocusPolicy(Qt::StrongFocus);
	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
}

View::~View()
{
	delete myBackMenu;
}

void View::initCursors()
{
// 	if (!defCursor)
// 		defCursor = new QCursor(Qt::ArrowCursor);
// 	if (!handCursor)
// 		handCursor = new QCursor(Qt::PointingHandCursor);
// 	if (!panCursor)
// 		panCursor = new QCursor(Qt::SizeAllCursor);
// 	if (!globPanCursor)
// 		globPanCursor = new QCursor(Qt::CrossCursor);
// 	if (!zoomCursor)
// 		zoomCursor = new QCursor(QPixmap(ApplicationCommonWindow::getResourceDir() + QString("/") + QObject::tr("ICON_CURSOR_ZOOM")));
// 	if (!rotCursor)
// 		rotCursor = new QCursor(QPixmap(ApplicationCommonWindow::getResourceDir() + QString("/") + QObject::tr("ICON_CURSOR_ROTATE")));
}