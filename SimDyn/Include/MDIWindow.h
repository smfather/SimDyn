#ifndef MDIWINDOW_H
#define MDIWINDOW_H

#include <QMainWindow>

class DocumentCommon;
class View;

class MDIWindow : public QMainWindow
{
	Q_OBJECT

public:
	MDIWindow(DocumentCommon* aDocument, QWidget* parent, Qt::WindowFlags wflags);
	MDIWindow(View* aView, DocumentCommon* aDocument, QWidget* parent, Qt::WindowFlags wflags);
	~MDIWindow();

protected:
	DocumentCommon*            myDocument;
	View*                      myView;
};

#endif