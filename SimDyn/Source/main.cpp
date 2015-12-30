#include "simdyn.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SimDyn w;
	w.show();
	return a.exec();
}
