/********************************************************************************
** Form generated from reading UI file 'page.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE_H
#define UI_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Page
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QLabel *lableWelcome;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Page)
    {
        if (Page->objectName().isEmpty())
            Page->setObjectName("Page");
        Page->resize(1184, 672);
        Page->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(Page);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(900, 300, 111, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe Script")});
        font.setPointSize(24);
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8(""));
        lableWelcome = new QLabel(centralwidget);
        lableWelcome->setObjectName("lableWelcome");
        lableWelcome->setGeometry(QRect(60, 300, 361, 41));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Tempus Sans ITC")});
        font1.setPointSize(26);
        lableWelcome->setFont(font1);
        lableWelcome->setStyleSheet(QString::fromUtf8(""));
        Page->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Page);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1184, 26));
        Page->setMenuBar(menubar);
        statusbar = new QStatusBar(Page);
        statusbar->setObjectName("statusbar");
        Page->setStatusBar(statusbar);

        retranslateUi(Page);

        QMetaObject::connectSlotsByName(Page);
    } // setupUi

    void retranslateUi(QMainWindow *Page)
    {
        Page->setWindowTitle(QCoreApplication::translate("Page", "Page", nullptr));
#if QT_CONFIG(tooltip)
        pushButton->setToolTip(QCoreApplication::translate("Page", "Click me!", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton->setText(QCoreApplication::translate("Page", "Play", nullptr));
#if QT_CONFIG(tooltip)
        lableWelcome->setToolTip(QCoreApplication::translate("Page", "Click Play!", nullptr));
#endif // QT_CONFIG(tooltip)
        lableWelcome->setText(QCoreApplication::translate("Page", "Welcome to Game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Page: public Ui_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE_H
