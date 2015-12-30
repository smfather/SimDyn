#include "simdyn.h"

SimDyn::SimDyn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	SetUp();
	QMainWindow::show();
}

SimDyn::~SimDyn()
{

}

bool SimDyn::SetUp()
{
	act_new = new QAction(QIcon(":/Resources/new.png"), tr("&New"), this);
	act_new->setStatusTip(tr("New"));
	connect(act_new, SIGNAL(triggered()), this, SLOT(slot_new));

	ui.mainToolBar->addAction(act_new);
	return true;
}

void SimDyn::slot_new()
{

}

void SimDyn::slot_open()
{

}

void SimDyn::slot_save()
{

}