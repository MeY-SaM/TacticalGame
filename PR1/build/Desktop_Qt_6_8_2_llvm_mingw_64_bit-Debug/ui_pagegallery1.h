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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageGallery1
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pageGallery1)
    {
        if (pageGallery1->objectName().isEmpty())
            pageGallery1->setObjectName("pageGallery1");
        pageGallery1->resize(800, 600);
        centralwidget = new QWidget(pageGallery1);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 10, 101, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe Print")});
        font.setPointSize(18);
        font.setBold(true);
        pushButton->setFont(font);
        pageGallery1->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pageGallery1);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        pageGallery1->setMenuBar(menubar);
        statusbar = new QStatusBar(pageGallery1);
        statusbar->setObjectName("statusbar");
        pageGallery1->setStatusBar(statusbar);

        retranslateUi(pageGallery1);

        QMetaObject::connectSlotsByName(pageGallery1);
    } // setupUi

    void retranslateUi(QMainWindow *pageGallery1)
    {
        pageGallery1->setWindowTitle(QCoreApplication::translate("pageGallery1", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("pageGallery1", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageGallery1: public Ui_pageGallery1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEGALLERY1_H
