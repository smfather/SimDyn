#ifndef SIMDYN_H
#define SIMDYN_H

#include <QtWidgets/QMainWindow>
#include "DocumentCommon.h"
#include "ui_simdyn.h"
#include <QList>
#include <QAction>
#include <QMdiArea>
#include <QToolBar>
#include <QMenu>

class SimDyn : public QMainWindow
{
	Q_OBJECT

public:
	enum { FILE_NEW_ID = 0, FILE_CLOSE_ID,};

	SimDyn(QWidget *parent = 0);
	~SimDyn();

	static QMdiArea* getWorkspace();
	static SimDyn* getApplication();

private slots:
	DocumentCommon* onNewDoc();
	void onCloseWindow();
// 	void slot_open();
// 	void slot_save();

protected:
	virtual DocumentCommon* createNewDocument();

public slots:
	virtual void                    onSelectionChanged();

private:
// 	QAction *act_new;
// 	QAction *act_open;
// 	QAction *act_save;
	int myNbDocuments;
	QList<QAction*> myStdActions;
	QToolBar* myStdToolBar;

	QMenu* myFilePopup;
	bool SetUp();

protected:
	QList<DocumentCommon*>          myDocuments;

private:
	Ui::SimDynClass ui;
};

#endif // SIMDYN_H
