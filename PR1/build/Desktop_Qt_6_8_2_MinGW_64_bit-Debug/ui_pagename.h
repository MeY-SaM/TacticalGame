/********************************************************************************
** Form generated from reading UI file 'pagename.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGENAME_H
#define UI_PAGENAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageName
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pageName)
    {
        if (pageName->objectName().isEmpty())
            pageName->setObjectName("pageName");
        pageName->resize(1184, 672);
        centralwidget = new QWidget(pageName);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(470, 470, 241, 71));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe Print")});
        font.setPointSize(22);
        font.setBold(true);
        pushButton->setFont(font);
        lineEdit = new QLineEdit(centralwidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(244, 270, 261, 131));
        QFont font1;
        font1.setPointSize(18);
        font1.setBold(true);
        lineEdit->setFont(font1);
        lineEdit->setTabletTracking(false);
        lineEdit->setFrame(true);
        lineEdit_2 = new QLineEdit(centralwidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(687, 270, 261, 131));
        lineEdit_2->setFont(font1);
        pageName->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pageName);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1184, 26));
        pageName->setMenuBar(menubar);
        statusbar = new QStatusBar(pageName);
        statusbar->setObjectName("statusbar");
        pageName->setStatusBar(statusbar);

        retranslateUi(pageName);

        QMetaObject::connectSlotsByName(pageName);
    } // setupUi

    void retranslateUi(QMainWindow *pageName)
    {
        pageName->setWindowTitle(QCoreApplication::translate("pageName", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("pageName", "Start game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageName: public Ui_pageName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGENAME_H
