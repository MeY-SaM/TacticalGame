#include "pagename.h"
#include "ui_pagename.h"

#include "QMessageBox"

pageName::pageName(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pageName)
{
    ui->setupUi(this);

    resize(1184,672);
    setWindowTitle("Name");
    setFixedSize(1184,672);
    setStyleSheet("QMainWindow { background-image:url(:/new/prefix1/pageName.jpg) ; }");


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
    ui->lineEdit->setStyleSheet("QLineEdit { background: transparent; border: none; color: rgb(245, 200, 110); }");
    ui->lineEdit->setAlignment(Qt::AlignCenter);
    ui->lineEdit->setPlaceholderText("Enter your Name");



    ui->lineEdit_2->setStyleSheet("QLineEdit { background: transparent; border: none; color: rgb(245, 200, 110); }");
    ui->lineEdit_2->setAlignment(Qt::AlignCenter);
    ui->lineEdit_2->setPlaceholderText("Enter your Name");


}

pageName::~pageName()
{
    delete ui;
}

void pageName::on_pushButton_clicked()
{    QString a,b;
    a= ui->lineEdit->text();
    b= ui->lineEdit_2->text();
    if(a =="" && b=="")
    {
        QMessageBox::warning(this,"Pay attention","Enter your name first");
    }
    else
    {

    }
}


