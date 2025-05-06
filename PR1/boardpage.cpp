#include "boardpage.h"
#include "ui_boardpage.h"

boardpage::boardpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::boardpage)
{
    ui->setupUi(this);

}

boardpage::~boardpage()
{
    delete ui;
}
