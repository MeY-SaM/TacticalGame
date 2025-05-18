#include "pagegallery1.h"
#include "ui_pagegallery1.h"
#include "page1.h"

pageGallery1::pageGallery1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pageGallery1)
{
    ui->setupUi(this);

    resize(1184,672);
    setWindowTitle("Gallery");
    setFixedSize(1184,672);
    setStyleSheet("QMainWindow { background-image: url(:/new/prefix1/pageGallery.jpg) ; }");

    ui->pushButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color:rgb(245, 200, 110);"
        "}"
        "QPushButton:hover {"
        "    color:white;"
        "}"
        );

}

pageGallery1::~pageGallery1()
{
    delete ui;
}

void pageGallery1::on_pushButton_clicked()
{
    page1 *w1 = new page1;
    w1->show();
    this->hide();
}

