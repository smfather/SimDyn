#ifndef SIMDYN_H
#define SIMDYN_H

#include <QtWidgets/QMainWindow>
#include "ui_simdyn.h"

class SimDyn : public QMainWindow
{
	Q_OBJECT

public:
	SimDyn(QWidget *parent = 0);
	~SimDyn();

	private slots:
	void slot_new();
	void slot_open();
	void slot_save();

private:
	QAction *act_new;
	QAction *act_open;
	QAction *act_save;

	bool SetUp();

private:
	Ui::SimDynClass ui;
};

#endif // SIMDYN_H
