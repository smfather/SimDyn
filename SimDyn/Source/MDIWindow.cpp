#include "MDIWindow.h"

#include "View.h"
#include "DocumentCommon.h"
#include "simdyn.h"

#include <QFrame>
#include <QToolBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMainWindow> 
#include <QVBoxLayout>

MDIWindow::MDIWindow(View* aView,
	DocumentCommon* aDocument,
	QWidget* parent,
	Qt::WindowFlags wflags)
	: QMainWindow(parent, wflags)
{
	myView = aView;
	myDocument = aDocument;
}

MDIWindow::MDIWindow(DocumentCommon* aDocument, QWidget* parent, Qt::WindowFlags wflags)
	: QMainWindow(parent, wflags)
{
	QFrame *vb = new QFrame(this);

	QVBoxLayout *layout = new QVBoxLayout(vb);
	layout->setMargin(0);

	vb->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);

	setCentralWidget(vb);

	myDocument = aDocument;
	myView = new View(myDocument->getContext(), vb);
	layout->addWidget(myView);

	connect(myView, SIGNAL(selectionChanged()),
		this, SIGNAL(selectionChanged()));

// 	createViewActions();
// 	createRaytraceActions();

	resize(sizeHint());

	setFocusPolicy(Qt::StrongFocus);
}

MDIWindow::~MDIWindow()
{
}