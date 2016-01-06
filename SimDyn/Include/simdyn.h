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
	enum { FILE_NEW_ID = 0, FILE_CLOSE_ID, FILE_PREF_USE_VBO, FILE_QUIT, VIEW_TOOL, VIEW_STATUS, HELP_ABOUT};
	enum { ToolWireframeId, ToolShadingId, ToolColorId, ToolMaterialId, ToolTransparencyId, ToolDeleteId };

	SimDyn(QWidget *parent = 0);
	~SimDyn();

	static QMdiArea* getWorkspace();
	static SimDyn* getApplication();
	QList<QAction*>*                 getToolActions();
	QList<QAction*>*                 getMaterialActions();
	virtual void                     updateFileActions();

public slots:
	DocumentCommon*					onNewDoc();
	void							onCloseWindow();
	void                            onUseVBO();
	virtual void                    onCloseDocument(DocumentCommon* theDoc);
	virtual void                    onSelectionChanged();
	virtual void                    onAbout();
	void                            onViewToolBar();
	void                            onViewStatusBar();
	void                            onToolAction();
	void                            onCreateNewView();
	void                            onWindowActivated(QWidget * w);
	void                            windowsMenuAboutToShow();
	void                            windowsMenuActivated(bool checked/*int id*/);
	void                            onSetMaterial(int theMaterial);
// 	void slot_open();
// 	void slot_save();

protected:
	virtual DocumentCommon* createNewDocument();

private:
	bool SetUp();
	void                            createStandardOperations();
	void                            createCasCadeOperations();
	void                            createWindowPopup();

protected:
	virtual void                    resizeEvent(QResizeEvent*);
	bool                            isDocument();
	QMenu*                          getFilePopup();
	QAction*                        getFileSeparator();
	QToolBar*                       getCasCadeBar();

private:
	int                             myNbDocuments;
	bool                            myIsDocuments;
	QAction*                        myFileSeparator;
	QList<QAction*>					myStdActions;
	QList<QAction*>                 myToolActions;
	QList<QAction*>                 myMaterialActions;
	//QList<DocumentCommon*>          myDocuments;

	QToolBar*						myStdToolBar;
	QToolBar*                       myCasCadeBar;
	QMenu*                          myFilePopup;
	QMenu*                          myWindowPopup;

protected:
	QList<DocumentCommon*>          myDocuments;

private:
	Ui::SimDynClass ui;
};

#endif // SIMDYN_H
