#include "simdyn.h"
#include <QFrame>
#include <QMdiArea>
#include <QVBoxLayout>

static SimDyn* stApp = 0;
static QMdiArea * stWs = 0;

SimDyn::SimDyn(QWidget *parent)
	: QMainWindow(parent)
{
	stApp = this;
	QFrame *vb = new QFrame(this);

	QVBoxLayout *layout = new QVBoxLayout(vb);
	layout->setMargin(0);

	vb->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
	stWs = new QMdiArea(vb);
	layout->addWidget(stWs);
	setCentralWidget(vb);

	//ui.setupUi(this);
	SetUp();
	//QMainWindow::show();
}

SimDyn::~SimDyn()
{

}

bool SimDyn::SetUp()
{
	QAction *fileNewAction, *fileCloseAction;

	fileNewAction = new QAction(QIcon(":/Resources/new.png"), tr("&new"), this);
	fileNewAction->setStatusTip(tr("New"));
	connect(fileNewAction, SIGNAL(triggered()), this, SLOT(onNewDoc()));
	myStdActions.insert(FILE_NEW_ID, fileNewAction);

	fileCloseAction = new QAction(QIcon(":/Resources/close.png"), tr("&close"), this);
	fileCloseAction->setStatusTip(tr("Close"));
	connect(fileCloseAction, SIGNAL(triggered()), this, SLOT(onCloseWindow()));
	myStdActions.insert(FILE_CLOSE_ID, fileCloseAction);

	myStdToolBar = addToolBar(tr("File Operations"));
	myStdToolBar->addAction(fileNewAction);
	myStdToolBar->addAction(fileCloseAction);

	myFilePopup = new QMenu(this);
	myFilePopup = menuBar()->addMenu(tr("File"));
	myFilePopup->addAction(fileNewAction);
	myFilePopup->addAction(fileCloseAction);
	//myFilePopup->addAction(fileQuitAction);
// 	act_new = new QAction(QIcon(":/Resources/new.png"), tr("&New"), this);
// 	act_new->setStatusTip(tr("New"));
// 	connect(act_new, SIGNAL(triggered()), this, SLOT(slot_new));
// 
// 	ui.mainToolBar->addAction(act_new);
	return true;
}

QMdiArea * SimDyn::getWorkspace()
{
	return stWs;
}

DocumentCommon* SimDyn::createNewDocument()
{
	return new DocumentCommon(++myNbDocuments, this);
}

DocumentCommon* SimDyn::onNewDoc()
{
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

}

void SimDyn::onSelectionChanged()
{
// 	QMdiArea* ws = SimDyn::getWorkspace();
// 	DocumentCommon* doc;
// 
// 	if (!qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget()))
// 		return;
// 
// 	doc = (qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget()))->getDocument();
// 	Handle(AIS_InteractiveContext) context = doc->getContext();
// 
// 	bool OneOrMoreInShading = false;
// 	bool OneOrMoreInWireframe = false;
// 	int numSel = context->NbSelected();
// 	if (numSel)
// 	{
// 		for (context->InitCurrent(); context->MoreCurrent(); context->NextCurrent())
// 		{
// 			if (context->IsDisplayed(context->Current(), 1))
// 				OneOrMoreInShading = true;
// 			if (context->IsDisplayed(context->Current(), 0))
// 				OneOrMoreInWireframe = true;
// 		}
// 		myToolActions.at(ToolWireframeId)->setEnabled(OneOrMoreInShading);
// 		myToolActions.at(ToolShadingId)->setEnabled(OneOrMoreInWireframe);
// 		myToolActions.at(ToolColorId)->setEnabled(true);
// 		myToolActions.at(ToolMaterialId)->setEnabled(true);
// 		myToolActions.at(ToolTransparencyId)->setEnabled(OneOrMoreInShading);
// 		myToolActions.at(ToolDeleteId)->setEnabled(true);
// 	}
// 	else
// 	{
// 		myToolActions.at(ToolWireframeId)->setEnabled(false);
// 		myToolActions.at(ToolShadingId)->setEnabled(false);
// 		myToolActions.at(ToolColorId)->setEnabled(false);
// 		myToolActions.at(ToolMaterialId)->setEnabled(false);
// 		myToolActions.at(ToolTransparencyId)->setEnabled(false);
// 		myToolActions.at(ToolDeleteId)->setEnabled(false);
// 	}
}



//void SimDyn::slot_open()
//{
//
//}
//
//void SimDyn::slot_save()
//{
//
//}