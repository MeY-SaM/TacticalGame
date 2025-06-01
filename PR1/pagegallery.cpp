#include "pagegallery.h"
#include "ui_pagegallery.h"
#include "page1.h"

#include <QTabWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QTabWidget>

void pageGallery::makeTransparent(QWidget* widget) {
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setAutoFillBackground(false);
}

pageGallery::pageGallery(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pageGallery)
{
    ui->setupUi(this);

    resize(1184, 672);
    setWindowTitle("Gallery");
    setFixedSize(1184, 672);


    setStyleSheet("QMainWindow { background-image: url(:/new/prefix1/pageGallery.jpg); }");

    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: rgb(245, 200, 110);"
        "}"
        "QPushButton:hover {"
        "    color: white;"
        "}"
        );

    // ---------- QTabWidget ----------
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setGeometry(0, 34, 1184, 640);
    tabWidget->setAttribute(Qt::WA_TranslucentBackground);
    tabWidget->setStyleSheet(R"(
        QTabWidget::pane {
            background: transparent;
            border: none;
        }
        QTabBar::tab {
            background: transparent;
            color: rgb(245, 200, 110);
            padding: 6px 12px;
            font-size: 18px;
            font-family: Segoe Print;
        }
        QTabBar::tab:selected {
            color: white;
            font-weight: bold;
        }
        QTabBar::tab:hover {
            color: white;
        }
    )");

    // ---------------- Tab 1 8 Buttons ----------------
    QWidget *tab1 = new QWidget;
    makeTransparent(tab1);
    QWidget *scrollContent = new QWidget;
    QGridLayout *layout1 = new QGridLayout(scrollContent);

    layout1->setVerticalSpacing(40);

    QString imagePaths[] = {
        ":/Water Walking/angus.png",
        ":/Water Walking/billy.png",
        ":/Water Walking/bunka.png",
        ":/Water Walking/colonelbaba.png",
        ":/Water Walking/duraham.png",
        ":/Water Walking/medusa.png",
        ":/Water Walking/reketon.png",
        ":/Water Walking/sanka.png"
    };


    for (int i = 0; i < 8; ++i) {
        QPushButton *btn = new QPushButton;
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #444444;
                color: white;
                padding: 6px;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #666666;
            }
        )");
        btn->setFixedSize(250, 350);
        QIcon buttonIcon(imagePaths[i]);
        btn->setIcon(buttonIcon);
        btn->setIconSize(QSize(250, 350));
        layout1->addWidget(btn, i / 3, i % 3);
    }
    scrollContent->setMinimumSize(scrollContent->sizeHint());

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);

    scrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    scrollArea->viewport()->setStyleSheet("background: transparent;");

    QVBoxLayout *tabLayout = new QVBoxLayout(tab1);
    tabLayout->addWidget(scrollArea);
    tabWidget->addTab(tab1, "Water Walking");

    // ---------------- Tab 2 13 Buttons ----------------
    QWidget *tab2 = new QWidget;
    makeTransparent(tab2);
    QWidget *scrollContent2 = new QWidget;
    QGridLayout *layout2 = new QGridLayout(scrollContent2);

    layout2->setVerticalSpacing(40);

    QString imagesPaths[] = {
        ":/Grounded/boi.png",
        ":/Grounded/eloi.png",
        ":/Grounded/elsa.png",
        ":/Grounded/frost.png",
        ":/Grounded/kabu.png",
        ":/Grounded/kanar.png",
        ":/Grounded/karissa.png",
        ":/Grounded/khan.png",
        ":/Grounded/rajakal.png",
        ":/Grounded/salih.png",
        ":/Grounded/sirlamorak.png",
        ":/Grounded/sirphilip.png",
        ":/Grounded/tusk.png"
    };

    for (int i = 0; i < 13; ++i) {
        QPushButton *btn = new QPushButton;
        btn->setFixedSize(250, 350);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #444444;
                color: white;
                padding: 6px;
                border-radius: 4px;
            }
            QPushButton:hover {
                background-color: #666666;
            }
        )");
        QIcon buttonIcon(imagesPaths[i]);
        btn->setIcon(buttonIcon);
        btn->setIconSize(QSize(250, 350));
        layout2->addWidget(btn, i / 3, i % 3);


    }
    scrollContent2->setMinimumSize(scrollContent2->sizeHint());

    QScrollArea *scrollArea2 = new QScrollArea;
    scrollArea2->setWidget(scrollContent2);
    scrollArea2->setWidgetResizable(true);

    scrollArea2->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    scrollArea2->viewport()->setStyleSheet("background: transparent;");

    QVBoxLayout *tabLayout2 = new QVBoxLayout(tab2);
    tabLayout2->addWidget(scrollArea2);

    tabWidget->addTab(tab2, "Grounded");

    // ---------------- Tab 3 1 Button ----------------
    QWidget *tab3 = new QWidget;
    makeTransparent(tab3);

    QVBoxLayout *layout3 = new QVBoxLayout(tab3);
    QPushButton *btn3 = new QPushButton;
    btn3->setStyleSheet(R"(
        QPushButton {
            background-color: #444444;
            color: white;
            padding: 6px 12px;
            border-radius: 4px;
        }
        QPushButton:hover {
            background-color: #666666;
        }
    )");
    btn3->setFixedSize(250, 350);

    QIcon buttonIcon1(":/Flying/rambu.png");
    btn3->setIcon(buttonIcon1);
    btn3->setIconSize(QSize(250, 350));

    layout3->addStretch();
    layout3->addWidget(btn3, 0, Qt::AlignCenter);
    layout3->addStretch();
    tabWidget->addTab(tab3, "Flying");

    // ---------------- Tab 4 2 Buttons ----------------
    QWidget *tab4 = new QWidget;
    makeTransparent(tab4);
    QHBoxLayout *layout4 = new QHBoxLayout(tab4);
    QPushButton *btnA = new QPushButton;
    QPushButton *btnB = new QPushButton;
    btnA->setStyleSheet(R"(
        QPushButton {
            background-color: #444444;
            color: white;
            padding: 6px 12px;
            border-radius: 4px;
        }
        QPushButton:hover {
            background-color: #666666;
        }
    )");
    btnA->setFixedSize(250, 350);

    btnB->setStyleSheet(btnA->styleSheet());
    btnB->setFixedSize(250, 350);

    layout4->addStretch();
    layout4->addWidget(btnA);
    layout4->addSpacing(80);
    layout4->addWidget(btnB);
    layout4->addStretch();

    QIcon buttonIcon2(":/Floating/death.png");
    btnA->setIcon(buttonIcon2);
    btnA->setIconSize(QSize(250, 350));

    QIcon buttonIcon3(":/Floating/sabrina.png");
    btnB->setIcon(buttonIcon3);
    btnB->setIconSize(QSize(250, 350));


    tabWidget->addTab(tab4, "Floating");
}

pageGallery::~pageGallery()
{
    delete ui;
}

void pageGallery::on_pushButton_clicked()
{
    page1 *w1 = new page1;
    w1->show();
    this->hide();
}
