/********************************************************************************
** Form generated from reading UI file 'page1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGE1_H
#define UI_PAGE1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_page1
{
public:
    QWidget *centralwidget;
    QPushButton *pushButtonGallery;
    QPushButton *pushButtonStart;
    QPushButton *pushButtonDis;
    QPushButton *pushButtonSet;
    QMenuBar *menubar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *page1)
    {
        if (page1->objectName().isEmpty())
            page1->setObjectName("page1");
        page1->resize(1184, 672);
        page1->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(page1);
        centralwidget->setObjectName("centralwidget");
        pushButtonGallery = new QPushButton(centralwidget);
        pushButtonGallery->setObjectName("pushButtonGallery");
        pushButtonGallery->setGeometry(QRect(780, 160, 161, 61));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe Print")});
        font.setPointSize(22);
        font.setBold(true);
        pushButtonGallery->setFont(font);
        pushButtonGallery->setFocusPolicy(Qt::FocusPolicy::NoFocus);
        pushButtonGallery->setToolTipDuration(-1);
        pushButtonGallery->setAutoFillBackground(true);
        pushButtonStart = new QPushButton(centralwidget);
        pushButtonStart->setObjectName("pushButtonStart");
        pushButtonStart->setGeometry(QRect(60, 160, 441, 61));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Segoe Print")});
        font1.setPointSize(18);
        font1.setBold(true);
        pushButtonStart->setFont(font1);
        pushButtonDis = new QPushButton(centralwidget);
        pushButtonDis->setObjectName("pushButtonDis");
        pushButtonDis->setGeometry(QRect(10, 380, 111, 41));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("Segoe Print")});
        font2.setPointSize(11);
        font2.setBold(true);
        pushButtonDis->setFont(font2);
        pushButtonSet = new QPushButton(centralwidget);
        pushButtonSet->setObjectName("pushButtonSet");
        pushButtonSet->setGeometry(QRect(10, 440, 111, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Segoe Print")});
        font3.setPointSize(12);
        font3.setBold(true);
        pushButtonSet->setFont(font3);
        page1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(page1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1184, 26));
        page1->setMenuBar(menubar);
        statusBar = new QStatusBar(page1);
        statusBar->setObjectName("statusBar");
        page1->setStatusBar(statusBar);

        retranslateUi(page1);

        QMetaObject::connectSlotsByName(page1);
    } // setupUi

    void retranslateUi(QMainWindow *page1)
    {
        page1->setWindowTitle(QCoreApplication::translate("page1", "MainWindow", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonGallery->setToolTip(QCoreApplication::translate("page1", "Click!", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonGallery->setText(QCoreApplication::translate("page1", "Gallery", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonStart->setToolTip(QCoreApplication::translate("page1", "Start!", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonStart->setText(QCoreApplication::translate("page1", "Start an Async PVP Game", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonDis->setToolTip(QCoreApplication::translate("page1", "Click!", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonDis->setText(QCoreApplication::translate("page1", "Discord", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonSet->setToolTip(QCoreApplication::translate("page1", "Click!", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonSet->setText(QCoreApplication::translate("page1", "Setting", nullptr));
    } // retranslateUi

};

namespace Ui {
    class page1: public Ui_page1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGE1_H
