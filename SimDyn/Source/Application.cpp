#include "Application.h"

#include "Translate.h"

#include <QMessageBox>
#include <stdlib.h>
#include <QMdiSubWindow>

ApplicationWindow::ApplicationWindow()
	: SimDyn(),
	myImportPopup(0),
	myExportPopup(0)
{
	createTranslatePopups();
}

ApplicationWindow::~ApplicationWindow()
{
}

void ApplicationWindow::createTranslatePopups()
{
	if (!myImportPopup)
		myImportPopup = new QMenu(QObject::tr("&amp;Import"), this);

	if (!myExportPopup)
		myExportPopup = new QMenu(QObject::tr("&amp;Export"), this);

	QAction* a;
	a = new QAction(QObject::tr("&amp;Brep ..."), this);
	a->setStatusTip(QObject::tr("Brep ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onImport()));
	myCasCadeTranslateActions.insert(FileImportBREPId, a);
	myImportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Brep ..."), this);
	a->setStatusTip(QObject::tr("Brep ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onExport()));
	myCasCadeTranslateActions.insert(FileExportBREPId, a);
	myExportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Csfdb ..."), this);
	a->setStatusTip(QObject::tr("Csfdb ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onImport()));
	myCasCadeTranslateActions.insert(FileImportCSFDBId, a);
	myImportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Csfdb ..."), this);
	a->setStatusTip(QObject::tr("Csfdb ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onExport()));
	myCasCadeTranslateActions.insert(FileExportCSFDBId, a);
	myExportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Iges ..."), this);
	a->setStatusTip(QObject::tr("Iges ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onImport()));
	myCasCadeTranslateActions.insert(FileImportIGESId, a);
	myImportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Iges ..."), this);
	a->setStatusTip(QObject::tr("Iges ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onExport()));
	myCasCadeTranslateActions.insert(FileExportIGESId, a);
	myExportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Step ..."), this);
	a->setStatusTip(QObject::tr("Step ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onImport()));
	myCasCadeTranslateActions.insert(FileImportSTEPId, a);
	myImportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Step ..."), this);
	a->setStatusTip(QObject::tr("Step ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onExport()));
	myCasCadeTranslateActions.insert(FileExportSTEPId, a);
	myExportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Stl ..."), this);
	a->setStatusTip(QObject::tr("Stl ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onExport()));
	myCasCadeTranslateActions.insert(FileExportSTLId, a);
	myExportPopup->addAction(a);

	a = new QAction(QObject::tr("&amp;Vrml ..."), this);
	a->setStatusTip(QObject::tr("Vrml ..."));
	connect(a, SIGNAL(triggered()), this, SLOT(onExport()));
	myCasCadeTranslateActions.insert(FileExportVRMLId, a);
	myExportPopup->addAction(a);

	myExportPopup->addSeparator();

	a = new QAction(QObject::tr("&amp;Image"), this);
	a->setStatusTip(QObject::tr("Image"));
	connect(a, SIGNAL(triggered()), this, SLOT(onExportImage()));
	myExportPopup->addAction(a);
}

void ApplicationWindow::updateFileActions()
{
	if (myDocuments.isEmpty())
	{
		if (!isDocument())
		{
			getFilePopup()->insertMenu(getFileSeparator(), myExportPopup);
			getFilePopup()->insertMenu(myExportPopup->menuAction(), myImportPopup);
			mySeparator = getFilePopup()->insertSeparator(myImportPopup->menuAction());
		}
		else
		{
			getFilePopup()->removeAction(myImportPopup->menuAction());
			getFilePopup()->removeAction(myExportPopup->menuAction());
			getFilePopup()->removeAction(mySeparator);
		}
	}
	SimDyn::updateFileActions();
}

void ApplicationWindow::onImport()
{
	QAction* a = (QAction*)sender();
	int type = translationFormat(a);
	if (type < 0)
		return;

	bool stat = translate(type, true);
	if (stat)
	{
		DocumentCommon* doc = qobject_cast<MDIWindow*>(getWorkspace()->activeSubWindow()->widget())->getDocument();
		doc->fitAll();
	}
}

void ApplicationWindow::onExport()
{
	QAction* a = (QAction*)sender();
	int type = translationFormat(a);
	if (type < 0)
		return;

	translate(type, false);
}

int ApplicationWindow::translationFormat(const QAction* a)
{
	int type = -1;
	for (int i = FileImportBREPId; i <= FileExportVRMLId; i++)
	{
		if (myCasCadeTranslateActions.at(i) == a)
		{
			type = i;
			break;
		}
	}
	switch (type)
	{
	case FileImportBREPId:
	case FileExportBREPId:
		type = Translate::FORMAT_BREP;
		break;
	case FileImportIGESId:
	case FileExportIGESId:
		type = Translate::FORMAT_IGES;
		break;
	case FileImportSTEPId:
	case FileExportSTEPId:
		type = Translate::FORAMT_STEP;
		break;
	case FileImportCSFDBId:
	case FileExportCSFDBId:
		type = Translate::FORMAT_CSFDB;
		break;
	case FileExportSTLId:
		type = Translate::FORMAT_STL;
		break;
	case FileExportVRMLId:
		type = Translate::FORMAT_VRML;
		break;
	}
	return type;
}

bool ApplicationWindow::translate(const int format, const bool import)
{
	static Translate* anTrans = createTranslator();
	DocumentCommon* doc = qobject_cast<MDIWindow*>(getWorkspace()->activeSubWindow()->widget())->getDocument();
	Handle(AIS_InteractiveContext) context = doc->getContext();
	bool status;
	if (import)
		status = anTrans->importModel(format, context);
	else
		status = anTrans->exportModel(format, context);

	if (!status)
	{
		QString msg = QObject::tr("INF_TRANSLATE_ERROR");
		if (!anTrans->info().isEmpty())
			msg += QString("\n") + anTrans->info();
		QMessageBox::critical(this, QObject::tr("TIT_ERROR"), msg, QObject::tr("BTN_OK"), QString::null, QString::null, 0, 0);
	}

	return status;
}

Translate* ApplicationWindow::createTranslator()
{
	Translate* anTrans = new Translate(this/*, "Translator"*/);
	return anTrans;
}

void ApplicationWindow::onSelectionChanged()
{
	SimDyn::onSelectionChanged();

	QMdiArea* ws = getWorkspace();
	DocumentCommon* doc = qobject_cast<MDIWindow*>(ws->activeSubWindow()->widget())->getDocument();
	Handle(AIS_InteractiveContext) context = doc->getContext();
	int numSel = context->NbSelected();

	myCasCadeTranslateActions.at(FileExportBREPId)->setEnabled(numSel);
	myCasCadeTranslateActions.at(FileExportCSFDBId)->setEnabled(numSel);
	myCasCadeTranslateActions.at(FileExportIGESId)->setEnabled(numSel);
	myCasCadeTranslateActions.at(FileExportSTEPId)->setEnabled(numSel);
	myCasCadeTranslateActions.at(FileExportSTLId)->setEnabled(numSel);
	myCasCadeTranslateActions.at(FileExportVRMLId)->setEnabled(numSel);
}

QString ApplicationWindow::getIEResourceDir()
{
	static QString aResourceDir =
		QString::fromUtf8(qgetenv("CSF_IEResourcesDefaults").constData());

	return aResourceDir;
}

void ApplicationWindow::onExportImage()
{
	MDIWindow* w = qobject_cast<MDIWindow*>(getWorkspace()->activeSubWindow()->widget());
	if (w)
		w->dump();
}


