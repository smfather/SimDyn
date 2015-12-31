#ifndef DOCUMENTCOMMON_H
#define DOCUMENTCOMMON_H

#include "MDIWindow.h"

#include <QObject>
#include <QList>

#include <AIS_InteractiveContext.hxx>
#include <V3d_Viewer.hxx>

class SimDyn;

class DocumentCommon : public QObject
{
	Q_OBJECT

public:
	DocumentCommon(const int, SimDyn*);
	~DocumentCommon();

	SimDyn* getApplication();
	Handle(AIS_InteractiveContext) getContext();

	public slots:
	virtual void onCreateNewView();

private:
	Handle(V3d_Viewer) Viewer(const Standard_ExtString theName,
							  const Standard_CString theDomain,
							  const Standard_Real theViewSize,
							  const V3d_TypeOfOrientation theViewProj,
							  const Standard_Boolean theComputedMode,
							  const Standard_Boolean theDefaultComputedMode);

protected:
	virtual MDIWindow*                   createNewMDIWindow();

protected:
	SimDyn *myApp;
	QList<MDIWindow*>			   myViews;
	Handle(V3d_Viewer)			   myViewer;
	Handle(AIS_InteractiveContext) myContext;
	int                            myIndex;
	int                            myNbViews;
};

#endif