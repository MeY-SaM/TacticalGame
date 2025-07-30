#include "pagegallery1.h"
#include "ui_pagegallery1.h"
#include "hexgame.h"


#include <QSplitter>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>


QString* imagePaths = new QString[] {
    ":/Water Walking/angus.png",
    ":/Water Walking/billy.png",
    ":/Water Walking/bunka.png",
    ":/Water Walking/colonelbaba.png",
    ":/Water Walking/duraham.png",
    ":/Water Walking/medusa.png",
    ":/Water Walking/reketon.png",
    ":/Water Walking/sanka.png",
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
    ":/Grounded/tusk.png",
    ":/Flying/rambu.png",
    ":/Floating/sabrina.png",
    ":/Floating/death.png"
};

void pageGallery1::setupSection(QWidget* container, bool isLeft) {
    QGridLayout* gridLayout = new QGridLayout(container);
    gridLayout->setHorizontalSpacing(15);
    gridLayout->setVerticalSpacing(20);
    gridLayout->setContentsMargins(0, 10, 0, 10);

    for (int i = 0; i < 24; ++i) {

        QPushButton* button = new QPushButton;
        button->setFixedSize(160, 220);
        button->setCheckable(true);


        button->setStyleSheet(
            "QPushButton {"
            "    border: none ;"
            "}"
            "QPushButton:hover {"
            "    border: 6px inset rgb(255, 203, 97);"
            "}"
            );

        QIcon buttonIcon(imagePaths[i]);
        button->setIcon(buttonIcon);
        button->setIconSize(QSize(150, 250));
        gridLayout->addWidget(button, i / 3, i % 3);

        if (isLeft) {
            leftButtons.append(button);
        } else {
            rightButtons.append(button);
        }


        connect(button, &QPushButton::clicked, this, [=]() {
            handleButtonClick(button, i, isLeft);
        });
    }
    container->setLayout(gridLayout);
}

pageGallery1::pageGallery1(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::pageGallery1)
{
    ui->setupUi(this);

    resize(1184, 672);
    setWindowTitle("Gallery1");
    setFixedSize(1184, 672);
    setStyleSheet("QMainWindow { background-image: url(:/new/prefix1/pageGallery.jpg); }");

    QWidget* centralWidget = new QWidget(this);
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);



    // Left----------------------------------------
    QWidget* leftContainer = new QWidget;
    QScrollArea* leftScrollArea = new QScrollArea;
    leftScrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    leftScrollArea->viewport()->setStyleSheet("background: transparent;");
    leftScrollArea->setWidgetResizable(true);
    leftScrollArea->setWidget(leftContainer);
    leftScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leftScrollArea->setLayoutDirection(Qt::RightToLeft);
    leftScrollArea->viewport()->setLayoutDirection(Qt::LeftToRight);

    setupSection(leftContainer,true);

    // Right---------------------------------------
    QWidget* rightContainer = new QWidget;
    QScrollArea* rightScrollArea = new QScrollArea;
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightContainer);
    rightScrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    rightScrollArea->viewport()->setStyleSheet("background: transparent;");
    rightScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setupSection(rightContainer,false);





    QWidget* buttonContainer = new QWidget();
    QVBoxLayout* buttonLayout = new QVBoxLayout(buttonContainer);
    buttonLayout->setContentsMargins(5, 0, 5, 0);
    buttonLayout->setSpacing(0);

    QPushButton* playButton = new QPushButton("P\n\nL\n\nA\n\nY", buttonContainer);
    playButton->setFixedSize(70, 672);
    playButton->setStyleSheet(
        "QPushButton {"
        "    background-color: transparent;"
        "    border: none;"
        "    color: rgb(245, 200, 110);"
        "    font-family: 'Segoe Print';"
        "    font-size: 32px;"
        "    font-weight: bold;"
        "    text-align: center;"
        "}"
        "QPushButton:hover {"
        "    color: white;"
        "}"
        );

    connect(playButton, &QPushButton::clicked, this, &pageGallery1::handlePlayButtonClick);


    buttonLayout->addStretch();
    buttonLayout->addWidget(playButton);
    buttonLayout->addStretch();


    mainLayout->addWidget(leftScrollArea);
    mainLayout->addWidget(buttonContainer);
    mainLayout->addWidget(rightScrollArea);



    setCentralWidget(centralWidget);
}
void pageGallery1::handleButtonClick(QPushButton* button, int index, bool isLeft) {
    QList<QPushButton*>& selectedButtons = isLeft ? selectedLeftButtons : selectedRightButtons;

    if (button->isChecked()) {
        if (selectedButtons.size() >= 8 && !selectedButtons.contains(button)) {
            button->setChecked(false);
            QMessageBox::warning(this, "Warning", "You cannot select more than 8 buttons in this section.\n Please deselect one first.");
            return;
        }
        if (!selectedButtons.contains(button)) {
            selectedButtons.append(button);
            button->setStyleSheet(
                "QPushButton {"
                "    border: 8px groove rgb(29, 205, 159);"
                "}"
                "QPushButton:hover {"
                "    border: 8px inset rgb(0, 255, 0);"
                "}"
                );
        }
    } else {
        if (selectedButtons.contains(button)) {
            selectedButtons.removeAll(button);
            button->setStyleSheet(
                "QPushButton {"
                "    border: none;"
                "}"
                "QPushButton:hover {"
                "    border: 8px inset rgb(255, 203, 97);"
                "}"
                );
        }
    }


    // executeButtonAction(index);
}
void pageGallery1::handlePlayButtonClick() {
    if (selectedLeftButtons.size() != 8 || selectedRightButtons.size() != 8) {
        QMessageBox::warning(this, "Warning", "You must select exactly 8 buttons in each section before proceeding!");
        return;
    }

    HexGame* nextPage = new HexGame;
    nextPage->show();
    this->hide();
}




/*void pageGallery1::executeButtonAction(int index) {
    switch (index) {
    case 0:

    case 1:

    case 2:

    case 3:

    case 4:

    case 5:

    case 6:

    case 7:

    case 8:

    case 9:

    case 10:

    case 11:

    case 12:

    case 13:

    case 14:

    case 15:

    case 16:

    case 17:

    case 18:

    case 19:

    case 20:

    case 21:

    case 22:

    case 23:

    default:

    }
}*/

pageGallery1::~pageGallery1()
{
    delete ui;
    delete[] imagePaths;
}


