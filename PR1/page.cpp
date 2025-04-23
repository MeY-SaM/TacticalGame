#include "page.h"
#include "ui_page.h"
#include "page1.h"

Page::Page(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Page)
{
    ui->setupUi(this);

    resize(1184,672);
    setWindowTitle("Login");
    setFixedSize(1184,672);
    setStyleSheet("QMainWindow { background-image: url(:/new/prefix1/1.jpg); }");


    ui->lableWelcome->setStyleSheet("color: rgb(226, 191, 110); font-weight: bold;");
   // ui->pushButton->setStyleSheet("background: transparent;");
   ui->pushButton-> setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: rgb(226, 191, 110);"
        "}"
        "QPushButton:hover {"
        "    color:white;"
        "}"
        );




}

Page::~Page()
{
    delete ui;
}

void Page::on_pushButton_clicked()
{
    page1 *w1 = new page1;
    w1->show();
    this->hide();
}

