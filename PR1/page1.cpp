#include "page1.h"
#include "ui_page1.h"
#include <QIcon>
#include "pagegallery.h"
#include "pagename.h"
#include "pagegallery1.h"


page1::page1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::page1)
{
    ui->setupUi(this);

    resize(1184,672);
    setWindowTitle("Start");
    setFixedSize(1184,672);
    setStyleSheet("QMainWindow { background-image:url(:/new/prefix1/dragon1.jpg) ; }");


    ui->pushButtonGallery1-> setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: rgb(245, 200, 110);"
        "}"
        "QPushButton:hover {"
        "    color:white;"
        "}"
        );
    ui->pushButtonGallery2->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color:rgb(245, 200, 110);"
        "}"
        "QPushButton:hover {"
        "    color:white;"
        "}"
        );
    ui->pushButtonStart-> setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color:rgb(245, 200, 110);"
        "}"
        "QPushButton:hover {"
        "    color:white;"
        "}"
        );

    QIcon icon(":/new/prefix1/discord.png");
    ui->pushButtonDis->setIcon(icon);
    ui->pushButtonDis->setIconSize(QSize(48, 48));
    ui->pushButtonDis->setStyleSheet("QPushButton { "
                                     "background-color: transparent;"
                                     "    color:rgb(245, 200, 110);"
                                     "}");


    QIcon Icon(":/new/prefix1/setting.png");
    ui->pushButtonSet->setIcon(Icon);
    ui->pushButtonSet->setIconSize(QSize(48, 48));
    ui->pushButtonSet->setStyleSheet("QPushButton { "
                                     "background-color: transparent;"
                                     "    color:rgb(245, 200, 110);"
                                     "}");


}

page1::~page1()
{
    delete ui;
}

void page1::on_pushButtonGallery1_clicked()
{
    pageGallery *w1 = new pageGallery;
    w1->show();
    this->hide();

}

void page1::on_pushButtonStart_clicked()
{
    pageName *w1 = new pageName;
    w1->show();
    this->hide();
}


void page1::on_pushButtonGallery2_clicked()
{
    pageGallery1 *w1 = new pageGallery1;
    w1->show();
    this->hide();
}




