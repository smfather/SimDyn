#include "simdyn.h"

#include "DocumentCommon.h"
#include "View.h"

#include <QFrame>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QStatusBar>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QApplication>
#include <QSignalMapper>

#include <Graphic3d_GraphicDriver.hxx>
#include <OpenGl_GraphicDriver.hxx>

#include <stdlib.h>

static SimDyn* stApp = 0;
static QMdiArea * stWs = 0;

SimDyn::SimDyn(QWidget *parent)
	: QMainWindow(parent)
	, myWindowPopup(0)
	, myFilePopup(0)
	, myCasCadeBar(0)
	, myStdToolBar(0)
{
	stApp = this;
	myNbDocuments = 0;
	myIsDocuments = false;
	QFrame *vb = new QFrame(this);

	QVBoxLayout *layout = new QVBoxLayout(vb);
	layout->setMargin(0);

	vb->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	stWs = new QMdiArea(vb);
	layout->addWidget(stWs);
	setCentralWidget(vb);

	createStandardOperations();
	createCasCadeOperations();
	//ui.setupUi(this);

	//SetUp();
	//QMainWindow::show();
}

SimDyn::~SimDyn()
{

}

void SimDyn::createStandardOperations()
{
	QAction *fileNewAction, *fileCloseAction, *filePrefUseVBOAction,
	*fileQuitAction, *viewToolAction, *viewStatusAction, *helpAboutAction;

	fileNewAction = new QAction(QIcon(":/Resources/new.png"), tr("&new"), this);
	fileNewAction->setStatusTip(tr("New"));
	fileNewAction->setShortcut(QObject::tr("CTRL+N"));
	connect(fileNewAction, SIGNAL(triggered()), this, SLOT(onNewDoc()));
	myStdActions.insert(FILE_NEW_ID, fileNewAction);

	fileCloseAction = new QAction(QIcon(":/Resources/close.png"), tr("&close"), this);
	fileCloseAction->setStatusTip(tr("Close"));
	fileCloseAction->setShortcut(QObject::tr("CTRL+W"));
	connect(fileCloseAction, SIGNAL(triggered()), this, SLOT(onCloseWindow()));
	myStdActions.insert(FILE_CLOSE_ID, fileCloseAction);

	filePrefUseVBOAction = new QAction(QIcon(":/Resources/close.png"), tr("&use vbo"), this);
	filePrefUseVBOAction->setStatusTip(tr("Use VBO"));
	connect(filePrefUseVBOAction, SIGNAL(triggered()), this, SLOT(onUseVBO()));
	filePrefUseVBOAction->setCheckable(true);
	filePrefUseVBOAction->setChecked(true);
	myStdActions.insert(FILE_PREF_USE_VBO, filePrefUseVBOAction);

	fileQuitAction = new QAction(QIcon(":/Resources/close.png"), tr("Quit"), this);
	fileQuitAction->setToolTip(tr("Quit"));
	fileQuitAction->setStatusTip("Quit");
	fileQuitAction->setShortcut(tr("CTRL+Q"));
	connect(fileQuitAction, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
	myStdActions.insert(FILE_QUIT, fileQuitAction);

	viewToolAction = new QAction(QIcon(":/Resources/close.png"), tr("&Tool bar"), this);
	viewToolAction->setToolTip(QObject::tr("Tool bar"));
	viewToolAction->setStatusTip(QObject::tr("Tool bar"));
	connect(viewToolAction, SIGNAL(triggered()), this, SLOT(onViewToolBar()));
	viewToolAction->setCheckable(true);
	viewToolAction->setChecked(true);
	myStdActions.insert(VIEW_TOOL, viewToolAction);

	viewStatusAction = new QAction(QIcon(":/Resources/close.png"), tr("&View status"), this);
	viewStatusAction->setToolTip(QObject::tr("View status"));
	viewStatusAction->setStatusTip(QObject::tr("View status"));
	connect(viewStatusAction, SIGNAL(triggered()), this, SLOT(onViewStatusBar()));
	viewStatusAction->setCheckable(true);
	viewStatusAction->setChecked(true);
	myStdActions.insert(VIEW_STATUS, viewStatusAction);

	helpAboutAction = new QAction(QIcon(":/Resources/close.png"), tr("Help"), this);
	helpAboutAction->setToolTip(QObject::tr("Help"));
	helpAboutAction->setStatusTip(QObject::tr("Help"));
	helpAboutAction->setShortcut(QObject::tr("F1"));
	connect(helpAboutAction, SIGNAL(triggered()), this, SLOT(onAbout()));
	myStdActions.insert(HELP_ABOUT, helpAboutAction);

	// create preferences menu
	QMenu* aPrefMenu = new QMenu(QObject::tr("&amp;Preferences"));
	aPrefMenu->addAction(filePrefUseVBOAction);

	myStdToolBar = addToolBar(tr("File Operations"));
	myStdToolBar->addAction(fileNewAction);
	myStdToolBar->addAction(fileCloseAction);

	myFilePopup = new QMenu(this);
	myFilePopup = menuBar()->addMenu(tr("File"));
	myFilePopup->addAction(fileNewAction);
	myFilePopup->addAction(fileCloseAction);
	myFileSeparator = myFilePopup->addSeparator();
	myFilePopup->addMenu(aPrefMenu);
	myFileSeparator = myFilePopup->addSeparator();
	myFilePopup->addAction(fileQuitAction);
	
	// add a view menu
	QMenu * view = new QMenu(this);

	view = menuBar()->addMenu(QObject::tr("MNU_VIEW"));
	view->addAction(viewToolAction);
	view->addAction(viewStatusAction);

	// add a help menu
	QMenu * help = new QMenu(this);
	menuBar()->addSeparator();
	help = menuBar()->addMenu(QObject::tr("MNU_HELP"));
	help->addAction(helpAboutAction);

	// populate a tool bar with some actions
	myStdToolBar = addToolBar(tr("File Operations"));
	myStdToolBar->addAction(fileNewAction);
	myStdToolBar->addAction(helpAboutAction);

	myStdActions.at(FILE_CLOSE_ID)->setEnabled(myDocuments.count() > 0);

	myStdActions.at(FILE_PREF_USE_VBO)->setEnabled(true);
}

void SimDyn::createCasCadeOperations()
{
	createWindowPopup();
	// populate a tool bar with some actions
	myCasCadeBar = addToolBar(tr("Shape Operations"));

	//QString dir = SimDyn::getResourceDir() + QString("/");
	QAction* a;

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Wireframe"), this);
	a->setToolTip(QObject::tr("TBR_TOOL_WIRE"));
	a->setStatusTip(QObject::tr("TBR_TOOL_WIRE"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(ToolWireframeId, a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Shading"), this);
	a->setToolTip(QObject::tr("TBR_TOOL_SHAD"));
	a->setStatusTip(QObject::tr("TBR_TOOL_SHAD"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(ToolShadingId, a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Color"), this);
	a->setToolTip(QObject::tr("Color"));
	a->setStatusTip(QObject::tr("Color"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(ToolColorId, a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Material"), this);
	a->setToolTip(QObject::tr("Material"));
	a->setStatusTip(QObject::tr("Material"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(ToolMaterialId, a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Transpatency"), this);
	a->setToolTip(QObject::tr("Transpatency"));
	a->setStatusTip(QObject::tr("Transpatency"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(ToolTransparencyId, a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Delete"), this);
	a->setToolTip(QObject::tr("Delete"));
	a->setStatusTip(QObject::tr("Delete"));
	connect(a, SIGNAL(triggered()), this, SLOT(onToolAction()));
	myToolActions.insert(ToolDeleteId, a);

	QSignalMapper* sm = new QSignalMapper(this);
	connect(sm, SIGNAL(mapped(int)), this, SLOT(onSetMaterial(int)));

	a = new QAction(QObject::tr("&Brass"), this);
	a->setToolTip(QObject::tr("Brass"));
	a->setStatusTip(QObject::tr("Brass"));
	sm->setMapping(a, (int)Graphic3d_NOM_BRASS);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_BRASS, a);

	a = new QAction(QObject::tr("&Bronze"), this);
	a->setToolTip(QObject::tr("Bronze"));
	a->setStatusTip(QObject::tr("Bronze"));
	sm->setMapping(a, (int)Graphic3d_NOM_BRONZE);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_BRONZE, a);

	a = new QAction(QObject::tr("&Copper"), this);
	a->setToolTip(QObject::tr("Copper"));
	a->setStatusTip(QObject::tr("Copper"));
	sm->setMapping(a, (int)Graphic3d_NOM_COPPER);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_COPPER, a);

	a = new QAction(QObject::tr("&Gold"), this);
	a->setToolTip(QObject::tr("Gold"));
	a->setStatusTip(QObject::tr("Gold"));
	sm->setMapping(a, (int)Graphic3d_NOM_GOLD);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_GOLD, a);

	a = new QAction(QObject::tr("&Pewter"), this);
	a->setToolTip(QObject::tr("Pewter"));
	a->setStatusTip(QObject::tr("Pewter"));
	sm->setMapping(a, (int)Graphic3d_NOM_PEWTER);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_PEWTER, a);

	a = new QAction(QObject::tr("&Plaster"), this);
	a->setToolTip(QObject::tr("Plaster"));
	a->setStatusTip(QObject::tr("Plaster"));
	sm->setMapping(a, (int)Graphic3d_NOM_PLASTER);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_PLASTER, a);

	a = new QAction(QObject::tr("&Plastic"), this);
	a->setToolTip(QObject::tr("Plastic"));
	a->setStatusTip(QObject::tr("Plastic"));
	sm->setMapping(a, (int)Graphic3d_NOM_PLASTIC);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_PLASTIC, a);

	a = new QAction(QObject::tr("&Silver"), this);
	a->setToolTip(QObject::tr("Silver"));
	a->setStatusTip(QObject::tr("Silver"));
	sm->setMapping(a, (int)Graphic3d_NOM_SILVER);
	connect(a, SIGNAL(triggered()), sm, SLOT(map()));
	myMaterialActions.insert(Graphic3d_NOM_SILVER, a);

	for (int i = 0; i < myToolActions.size(); i++)
		myCasCadeBar->addAction(myToolActions.at(i));
	myCasCadeBar->hide();
}

void SimDyn::createWindowPopup()
{
	if (!myWindowPopup)
	{
		myWindowPopup = new QMenu(QObject::tr("&amp;Window"), this);
		connect(myWindowPopup, SIGNAL(aboutToShow()),
			this, SLOT(windowsMenuAboutToShow()));
	}
}

void SimDyn::updateFileActions()
{
	if (myDocuments.isEmpty())
	{
		if (!myIsDocuments)
		{
			QAction *fileQuitAction, *windowAction;
			QList<QAction *> aListActions = myFilePopup->actions();
			for (int i = 0; i < aListActions.size(); i++)
			{
				if (aListActions.at(i)->text() == QObject::tr("&Quit"))
				{
					fileQuitAction = aListActions.at(i);
					break;
				}
			}

			if (!fileQuitAction)
				return;

			myIsDocuments = true;
			myCasCadeBar->show();

			QList<QAction *> aListMenuActions = menuBar()->actions();
			for (int i = 0; i < aListMenuActions.size(); i++)
			{
				if (aListMenuActions.at(i)->text() == QObject::tr("&Help"))
				{
					windowAction = aListMenuActions.at(i);
					break;
				}
			}

			if (!windowAction)
				return;

			menuBar()->insertMenu(windowAction, myWindowPopup);
		}
		else
		{
			myIsDocuments = false;
			myCasCadeBar->hide();
			menuBar()->removeAction(myWindowPopup->menuAction());
		}
	}
}

QMdiArea * SimDyn::getWorkspace()
{
	return stWs;
}

QMenu* SimDyn::getFilePopup()
{
	return myFilePopup;
}

QAction* SimDyn::getFileSeparator()
{
	return myFileSeparator;
}

DocumentCommon* SimDyn::createNewDocument()
{
	return new DocumentCommon(++myNbDocuments, this);
}

DocumentCommon* SimDyn::onNewDoc()
{
	updateFileActions();

	DocumentCommon* aDoc = createNewDocument();
	aDoc->onCreateNewView();
	
	onSelectionChanged();

	connect(aDoc, SIGNAL(sendCloseDocument(DocumentCommon*)),
		this, SLOT(onCloseDocument(DocumentCommon*)));
	connect(stWs, SIGNAL(windowActivated(QWidget*)),
		this, SLOT(onWindowActivated(QWidget*)));
	connect(aDoc, SIGNAL(selectionChanged()),
		this, SLOT(onSelectionChanged()));

	myDocuments.append(aDoc);
	myStdActions.at(FILE_CLOSE_ID)->setEnabled(myDocuments.count() > 0);

	return aDoc;
}

void SimDyn::onCloseWindow()
{
	stWs->activeSubWindow()->close();
}

void SimDyn::onUseVBO()
{
	MDIWindow* aWindow = qobject_cast<MDIWindow*> (stWs->activeSubWindow()->widget());

	if (NULL == aWindow)
		return;

	Handle(AIS_InteractiveContext) aContextAIS = aWindow->getDocument()->getContext();

	if (aContextAIS.IsNull())
		return;

	Handle(OpenGl_GraphicDriver) aDriver =
		Handle(OpenGl_GraphicDriver)::DownCast(aContextAIS->CurrentViewer()->Driver());

	if (!aDriver.IsNull())
	{
		aDriver->ChangeOptions().vboDisable = Standard_True;
	}
}

void SimDyn::onCloseDocument(DocumentCommon* theDoc)
{
	myDocuments.removeAll(theDoc);
	theDoc->removeViews();
	delete theDoc;
	updateFileActions();
	myStdActions.at(FILE_CLOSE_ID)->setEnabled(myDocuments.count() > 0);
}

void SimDyn::onViewToolBar()
{
	bool show = myStdActions.at(VIEW_TOOL)->isChecked();
	if (show == myStdToolBar->isVisible())
		return;
	if (show)
		myStdToolBar->show();
	else
		myStdToolBar->hide();
}

void SimDyn::onViewStatusBar()
{
	bool show = myStdActions.at(VIEW_TOOL)->isChecked();
	if (show == statusBar()->isVisible())
		return;
	if (show)
		statusBar()->show();
	else
		statusBar()->hide();
}

void SimDyn::onAbout()
{
	QMessageBox::information(this, QObject::tr("TIT_ABOUT"), QObject::tr("INF_ABOUT"), QObject::tr("BTN_OK"),
		QString::null, QString::null, 0, 0);
}

void SimDyn::onCreateNewView()
{
	MDIWindow* window = qobject_cast<MDIWindow*>(stWs->activeSubWindow()->widget());
	window->getDocument()->onCreateNewView();
}

void SimDyn::onWindowActivated(QWidget * w)
{
	if (w == NULL)
	{
		return;
	}

	MDIWindow* window = qobject_cast<MDIWindow*>(w);

	window->onWindowActivated();
}

void SimDyn::onToolAction()
{
	QAction* sentBy = (QAction*)sender();
	QMdiArea* ws = SimDyn::getWorkspace();
	DocumentCommon* doc = qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget())->getDocument();

	if (sentBy == myToolActions.at(ToolWireframeId))
		doc->onWireframe();

	if (sentBy == myToolActions.at(ToolShadingId))
		doc->onShading();

	if (sentBy == myToolActions.at(ToolColorId))
		doc->onColor();

	if (sentBy == myToolActions.at(ToolMaterialId))
		doc->onMaterial();

	if (sentBy == myToolActions.at(ToolTransparencyId))
		doc->onTransparency();

	if (sentBy == myToolActions.at(ToolDeleteId))
		doc->onDelete();
}

void SimDyn::onSelectionChanged()
{
	QMdiArea* ws = SimDyn::getWorkspace();
	DocumentCommon* doc;

	if (!qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget()))
		return;

	doc = (qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget()))->getDocument();
	Handle(AIS_InteractiveContext) context = doc->getContext();

	bool OneOrMoreInShading = false;
	bool OneOrMoreInWireframe = false;
	int numSel = context->NbSelected();
	if (numSel)
	{
		for (context->InitCurrent(); context->MoreCurrent(); context->NextCurrent())
		{
			if (context->IsDisplayed(context->Current(), 1))
				OneOrMoreInShading = true;
			if (context->IsDisplayed(context->Current(), 0))
				OneOrMoreInWireframe = true;
		}
		myToolActions.at(ToolWireframeId)->setEnabled(OneOrMoreInShading);
		myToolActions.at(ToolShadingId)->setEnabled(OneOrMoreInWireframe);
		myToolActions.at(ToolColorId)->setEnabled(true);
		myToolActions.at(ToolMaterialId)->setEnabled(true);
		myToolActions.at(ToolTransparencyId)->setEnabled(OneOrMoreInShading);
		myToolActions.at(ToolDeleteId)->setEnabled(true);
	}
	else
	{
		myToolActions.at(ToolWireframeId)->setEnabled(false);
		myToolActions.at(ToolShadingId)->setEnabled(false);
		myToolActions.at(ToolColorId)->setEnabled(false);
		myToolActions.at(ToolMaterialId)->setEnabled(false);
		myToolActions.at(ToolTransparencyId)->setEnabled(false);
		myToolActions.at(ToolDeleteId)->setEnabled(false);
	}
}

void SimDyn::onSetMaterial(int theMaterial)
{
	QMdiArea* ws = getWorkspace();
	DocumentCommon* doc = qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget())->getDocument();
	doc->onMaterial(theMaterial);
}

// QString SimDyn::getResourceDir()
// {
// 	static QString aResourceDir =
// 		QString::fromUtf8(qgetenv("CSF_ResourcesDefaults").constData());
// 
// 	return aResourceDir;
// }

void SimDyn::resizeEvent(QResizeEvent* e)
{
	QMainWindow::resizeEvent(e);
	statusBar()->setSizeGripEnabled(!isMaximized());
}

bool SimDyn::isDocument()
{
	return myIsDocuments;
}

QToolBar* SimDyn::getCasCadeBar()
{
	return myCasCadeBar;
}

void SimDyn::windowsMenuAboutToShow()
{
	myWindowPopup->clear();
	QAction* a;

	//QString dir = getResourceDir() + QString("/");

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Quit"), this);
	a->setToolTip(QObject::tr("TBR_WINDOW_NEW3D"));
	a->setStatusTip(QObject::tr("TBR_WINDOW_NEW3D"));
	connect(a, SIGNAL(triggered()), this, SLOT(onCreateNewView()));
	myWindowPopup->addAction(a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Quit"), this);
	a->setToolTip(QObject::tr("TBR_WINDOW_CASCADE"));
	a->setStatusTip(QObject::tr("TBR_WINDOW_CASCADE"));
	connect(a, SIGNAL(triggered()), stWs, SLOT(cascade()));
	myWindowPopup->addAction(a);

	a = new QAction(QIcon(":/Resources/close.png"), tr("&Quit"), this);
	a->setToolTip(QObject::tr("TBR_WINDOW_TILE"));
	a->setStatusTip(QObject::tr("TBR_WINDOW_TILE"));
	connect(a, SIGNAL(triggered()), stWs, SLOT(tile()));
	myWindowPopup->addAction(a);

	myWindowPopup->addSeparator();
	QList<QMdiSubWindow *> windows = stWs->subWindowList();
	for (int i = 0; i < windows.count(); ++i)
	{
		QAction* aAction = new QAction(windows.at(i)->windowTitle(), this);
		aAction->setCheckable(true);
		aAction->setData(i);
		myWindowPopup->addAction(aAction);
		connect(aAction, SIGNAL(toggled(bool)), this, SLOT(windowsMenuActivated(bool)));
		aAction->setChecked(stWs->activeSubWindow() == windows.at(i));
	}
}

void SimDyn::windowsMenuActivated(bool checked)
{
	QAction* aSender = qobject_cast<QAction*>(sender());
	if (!aSender)
		return;
	QWidget * w = stWs->subWindowList().at(aSender->data().toInt());
	if (w && checked)
		w->setFocus();
}

SimDyn* SimDyn::getApplication()
{
	return stApp;
}

QList<QAction*>* SimDyn::getToolActions()
{
	return &myToolActions;
}

QList<QAction*>* SimDyn::getMaterialActions()
{
	return &myMaterialActions;
}