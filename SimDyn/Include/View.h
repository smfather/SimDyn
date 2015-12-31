#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QAction>
#include <QList>

#include <AIS_InteractiveContext.hxx>
#include <V3d_View.hxx>

class TopoDS_Shape;
class QRubberBand;

class View : public QWidget
{
	Q_OBJECT

protected:
	enum CurrentAction3d {
		CurAction3d_Nothing, CurAction3d_DynamicZooming,
		CurAction3d_WindowZooming, CurAction3d_DynamicPanning,
		CurAction3d_GlobalPanning, CurAction3d_DynamicRotation
	};

public:
	enum ViewAction {
		ViewFitAllId, ViewFitAreaId, ViewZoomId, ViewPanId, ViewGlobalPanId,
		ViewFrontId, ViewBackId, ViewTopId, ViewBottomId, ViewLeftId, ViewRightId,
		ViewAxoId, ViewRotationId, ViewResetId, ViewHlrOffId, ViewHlrOnId
	};
	enum RaytraceAction { ToolRaytracingId, ToolShadowsId, ToolReflectionsId, ToolAntialiasingId };

	View(Handle(AIS_InteractiveContext) theContext, QWidget* parent);

	~View();

private:
	void                          initCursors();

private:
	bool                            myIsRaytracing;
	bool                            myIsShadowsEnabled;
	bool                            myIsReflectionsEnabled;
	bool                            myIsAntialiasingEnabled;

	bool                            myFirst;
	bool		                    myDrawRect;           // set when a rect is used for selection or magnify 
	Handle(V3d_View)                myView;
	Handle(AIS_InteractiveContext)  myContext;
	CurrentAction3d                 myCurrentMode;
	Standard_Integer                myXmin;
	Standard_Integer                myYmin;
	Standard_Integer                myXmax;
	Standard_Integer                myYmax;
	Quantity_Factor                 myCurZoom;
	Standard_Boolean                myHlrModeIsOn;

	QList<QAction*>*                myViewActions;
	QList<QAction*>*                myRaytraceActions;
	QMenu*                          myBackMenu;
	QRubberBand*                    myRectBand; //!< selection rectangle rubber band
};

#endif