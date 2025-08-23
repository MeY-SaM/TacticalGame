#include "pagegallery1.h"
#include "ui_pagegallery1.h"
#include "hexgame.h"
#include "agent.h"

#include <QSplitter>
#include <QScrollArea>
#include <QGridLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <algorithm>

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
/*
AgentInfo agentInfos[24] = {
    {"Angus", 400, 2, 100, 1, AgentType::WaterWalking},
    {"Billy", 320, 2, 90, 2, AgentType::WaterWalking},
    {"Bunka", 320, 3, 100, 1, AgentType::WaterWalking},
    {"ColonelBaba", 400, 2, 100, 1, AgentType::WaterWalking},
    {"Duraham", 320, 2, 100, 2, AgentType::WaterWalking},
    {"Medusa", 320, 2, 90, 2, AgentType::WaterWalking},
    {"Reketon", 320, 1, 90, 3, AgentType::WaterWalking},
    {"Sanka", 320, 3, 100, 1, AgentType::WaterWalking},
    {"Boi", 320, 2, 90, 1, AgentType::Grounded},
    {"Eloi", 320, 2, 90, 1, AgentType::Grounded},
    {"Elsa", 320, 2, 90, 1, AgentType::Grounded},
    {"Frost", 320, 2, 90, 1, AgentType::Grounded},
    {"Kabu", 320, 2, 90, 1, AgentType::Grounded},
    {"Kanar", 320, 2, 90, 1, AgentType::Grounded},
    {"Karissa", 320, 2, 90, 1, AgentType::Grounded},
    {"Khan", 320, 2, 90, 1, AgentType::Grounded},
    {"Rajakal", 320, 2, 90, 1, AgentType::Grounded},
    {"Salih", 320, 2, 90, 1, AgentType::Grounded},
    {"SirLamorak", 320, 2, 90, 1, AgentType::Grounded},
    {"SirPhilip", 320, 2, 90, 1, AgentType::Grounded},
    {"Tusk", 320, 2, 90, 1, AgentType::Grounded},
    {"Rambu", 320, 2, 90, 1, AgentType::Flying},
    {"Sabrina", 320, 2, 90, 1, AgentType::Floating},
    {"Death", 320, 2, 90, 1, AgentType::Floating}
};
*/
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

    // Left Container
    QWidget* leftContainer = new QWidget;
    QScrollArea* leftScrollArea = new QScrollArea;
    leftScrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    leftScrollArea->viewport()->setStyleSheet("background: transparent;");
    leftScrollArea->setWidgetResizable(true);
    leftScrollArea->setWidget(leftContainer);
    leftScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    leftScrollArea->setLayoutDirection(Qt::RightToLeft);
    leftScrollArea->viewport()->setLayoutDirection(Qt::LeftToRight);

    setupSection(leftContainer, true);

    // Right Container
    QWidget* rightContainer = new QWidget;
    QScrollArea* rightScrollArea = new QScrollArea;
    rightScrollArea->setWidgetResizable(true);
    rightScrollArea->setWidget(rightContainer);
    rightScrollArea->setStyleSheet("QScrollArea { border: none; background: transparent; }");
    rightScrollArea->viewport()->setStyleSheet("background: transparent;");
    rightScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setupSection(rightContainer, false);


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

void pageGallery1::handleButtonClick(QPushButton* button, int index, bool isLeft) {
    std::vector<int>& selectedIndices = isLeft ? selectedLeftIndices : selectedRightIndices;
    QList<QPushButton*>& selectedButtons = isLeft ? selectedLeftButtons : selectedRightButtons;

    if (button->isChecked()) {
        if (selectedButtons.size() >= 8 && !selectedButtons.contains(button)) {
            button->setChecked(false);
            QMessageBox::warning(this, "Warning", "You cannot select more than 8 buttons in this section.\nPlease deselect one first.");
            return;
        }
        if (!selectedButtons.contains(button)) {
            selectedButtons.append(button);
            selectedIndices.push_back(index);  // اضافه کردن اندیس
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
            auto it = std::find(selectedIndices.begin(), selectedIndices.end(), index);
            if (it != selectedIndices.end()) {
                selectedIndices.erase(it);
            }
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
}

void pageGallery1::handlePlayButtonClick() {
    if (selectedLeftIndices.size() != 8 || selectedRightIndices.size() != 8) {
        QMessageBox::warning(this, "Warning", "You must select exactly 8 buttons in each section before proceeding!");
        return;
    }

    HexGame* nextPage = new HexGame(selectedLeftIndices, selectedRightIndices);
    nextPage->show();
    this->hide();
}


pageGallery1::~pageGallery1()
{
    delete ui;
    delete[] imagePaths;
}
