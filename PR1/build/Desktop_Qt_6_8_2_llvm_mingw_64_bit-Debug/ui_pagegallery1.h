/********************************************************************************
** Form generated from reading UI file 'pagegallery1.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEGALLERY1_H
#define UI_PAGEGALLERY1_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageGallery1
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;

    void setupUi(QMainWindow *pageGallery1)
    {
        if (pageGallery1->objectName().isEmpty())
            pageGallery1->setObjectName("pageGallery1");
        pageGallery1->resize(1184, 672);
        centralwidget = new QWidget(pageGallery1);
        centralwidget->setObjectName("centralwidget");
        pageGallery1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pageGallery1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1184, 26));
        pageGallery1->setMenuBar(menubar);

        retranslateUi(pageGallery1);

        QMetaObject::connectSlotsByName(pageGallery1);
    } // setupUi

    void retranslateUi(QMainWindow *pageGallery1)
    {
        pageGallery1->setWindowTitle(QCoreApplication::translate("pageGallery1", "MainWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageGallery1: public Ui_pageGallery1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEGALLERY1_H
