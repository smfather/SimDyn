/********************************************************************************
** Form generated from reading UI file 'simdyn.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMDYN_H
#define UI_SIMDYN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SimDynClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimDynClass)
    {
        if (SimDynClass->objectName().isEmpty())
            SimDynClass->setObjectName(QStringLiteral("SimDynClass"));
        SimDynClass->resize(600, 400);
        menuBar = new QMenuBar(SimDynClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        SimDynClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SimDynClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SimDynClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(SimDynClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        SimDynClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(SimDynClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SimDynClass->setStatusBar(statusBar);

        retranslateUi(SimDynClass);

        QMetaObject::connectSlotsByName(SimDynClass);
    } // setupUi

    void retranslateUi(QMainWindow *SimDynClass)
    {
        SimDynClass->setWindowTitle(QApplication::translate("SimDynClass", "SimDyn", 0));
    } // retranslateUi

};

namespace Ui {
    class SimDynClass: public Ui_SimDynClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMDYN_H
