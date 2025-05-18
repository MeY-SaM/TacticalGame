#include "pagegallery.h"
#include "ui_pagegallery.h"
#include "page1.h"


pageGallery::pageGallery(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pageGallery)
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

