#include "pagegallery.h"
#include "ui_pagegallery.h"
#include "page1.h"

#include <QTabWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

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
    QGridLayout *layout1 = new QGridLayout(tab1);
    for (int i = 0; i < 8; ++i) {
        QPushButton *btn = new QPushButton(QString("Button %1").arg(i + 1));
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
        layout1->addWidget(btn, i / 4, i % 4);
    }
    tabWidget->addTab(tab1, "Water Walking");

    // ---------------- Tab 2 13 Buttons ----------------
    QWidget *tab2 = new QWidget;
    makeTransparent(tab2);
    QGridLayout *layout2 = new QGridLayout(tab2);
    for (int i = 0; i < 13; ++i) {
        QPushButton *btn = new QPushButton(QString("Button %1").arg(i + 1));
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
        layout2->addWidget(btn, i / 4, i % 4);
    }
    tabWidget->addTab(tab2, "Grounded");

    // ---------------- Tab 3 1 Button ----------------
    QWidget *tab3 = new QWidget;
    makeTransparent(tab3);
    QVBoxLayout *layout3 = new QVBoxLayout(tab3);
    QPushButton *btn3 = new QPushButton("Only Button");
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
    layout3->addStretch();
    layout3->addWidget(btn3, 0, Qt::AlignCenter);
    layout3->addStretch();
    tabWidget->addTab(tab3, "Flying");

    // ---------------- Tab 4 2 Buttons ----------------
    QWidget *tab4 = new QWidget;
    makeTransparent(tab4);
    QHBoxLayout *layout4 = new QHBoxLayout(tab4);
    QPushButton *btnA = new QPushButton("Button A");
    QPushButton *btnB = new QPushButton("Button B");
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
    btnB->setStyleSheet(btnA->styleSheet());
    layout4->addStretch();
    layout4->addWidget(btnA);
    layout4->addWidget(btnB);
    layout4->addStretch();
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
