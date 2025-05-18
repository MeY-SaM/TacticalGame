/********************************************************************************
** Form generated from reading UI file 'pagegallery.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PAGEGALLERY_H
#define UI_PAGEGALLERY_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pageGallery
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *pageGallery)
    {
        if (pageGallery->objectName().isEmpty())
            pageGallery->setObjectName("pageGallery");
        pageGallery->resize(800, 600);
        pageGallery->setStyleSheet(QString::fromUtf8(""));
        centralwidget = new QWidget(pageGallery);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 10, 101, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe Print")});
        font.setPointSize(18);
        font.setBold(true);
        pushButton->setFont(font);
        pageGallery->setCentralWidget(centralwidget);
        menubar = new QMenuBar(pageGallery);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        pageGallery->setMenuBar(menubar);
        statusbar = new QStatusBar(pageGallery);
        statusbar->setObjectName("statusbar");
        pageGallery->setStatusBar(statusbar);

        retranslateUi(pageGallery);

        QMetaObject::connectSlotsByName(pageGallery);
    } // setupUi

    void retranslateUi(QMainWindow *pageGallery)
    {
        pageGallery->setWindowTitle(QCoreApplication::translate("pageGallery", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("pageGallery", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pageGallery: public Ui_pageGallery {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PAGEGALLERY_H
