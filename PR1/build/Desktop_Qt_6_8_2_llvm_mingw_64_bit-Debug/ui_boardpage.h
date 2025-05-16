/********************************************************************************
** Form generated from reading UI file 'boardpage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BOARDPAGE_H
#define UI_BOARDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_boardpage
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *boardpage)
    {
        if (boardpage->objectName().isEmpty())
            boardpage->setObjectName("boardpage");
        boardpage->resize(800, 600);
        centralwidget = new QWidget(boardpage);
        centralwidget->setObjectName("centralwidget");
        boardpage->setCentralWidget(centralwidget);
        menubar = new QMenuBar(boardpage);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        boardpage->setMenuBar(menubar);
        statusbar = new QStatusBar(boardpage);
        statusbar->setObjectName("statusbar");
        boardpage->setStatusBar(statusbar);

        retranslateUi(boardpage);

        QMetaObject::connectSlotsByName(boardpage);
    } // setupUi

    void retranslateUi(QMainWindow *boardpage)
    {
        boardpage->setWindowTitle(QCoreApplication::translate("boardpage", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class boardpage: public Ui_boardpage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BOARDPAGE_H
