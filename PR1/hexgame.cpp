#include "hexgame.h"
#include "draggableagent.h"
#include "agent.h"
#include "boardimagepaths.h"
#include <QApplication>
#include <QDebug>
#include <cmath>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <queue>
#include <set>
#include <algorithm>
#include <random>

AgentInfo* agentInfos = new AgentInfo[24]{
    {"Angus", 400, 2, 100, 1, AgentType::WaterWalking},
    {"Billy", 320, 3, 90, 1, AgentType::WaterWalking},
    {"Bunka", 320, 3, 100, 1, AgentType::WaterWalking},
    {"ColonelBaba", 400, 2, 100, 1, AgentType::WaterWalking},
    {"Duraham", 320, 2, 100, 2, AgentType::WaterWalking},
    {"Medusa", 320, 2, 90, 2, AgentType::WaterWalking},
    {"Reketon", 320, 2, 80, 2, AgentType::WaterWalking},
    {"Sanka", 320, 3, 100, 1, AgentType::WaterWalking},
    {"Boi", 400, 2, 100, 1, AgentType::Grounded},
    {"Eloi", 240, 2, 100, 3, AgentType::Grounded},
    {"Elsa", 320, 2, 140, 2, AgentType::Grounded},
    {"Frost", 260, 2, 80, 2, AgentType::Grounded},
    {"Kabu", 400, 2, 120, 1, AgentType::Grounded},
    {"Kanar", 160, 2, 100, 2, AgentType::Grounded},
    {"Karissa", 280, 2, 80, 2, AgentType::Grounded},
    {"Khan", 320, 2, 90, 1, AgentType::Grounded},
    {"Rajakal", 320, 2, 130, 1, AgentType::Grounded},
    {"Salih", 400, 2, 80, 1, AgentType::Grounded},
    {"SirLamorak", 320, 3, 110, 1, AgentType::Grounded},
    {"SirPhilip", 400, 2, 100, 1, AgentType::Grounded},
    {"Tusk", 400, 2, 100, 1, AgentType::Grounded},
    {"Rambu", 320, 3, 120, 1, AgentType::Flying},
    {"Sabrina", 320, 3, 100, 1, AgentType::Floating},
    {"Death", 240, 3, 120, 2, AgentType::Floating}
};

HexGame::HexGame(QWidget *parent) : QWidget(parent) {
    setFixedSize(1184, 800);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(1184, 800);
    scene->setSceneRect(0, 0, 1184, 800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

HexGame::HexGame(const std::vector<int>& leftIndices, const std::vector<int>& rightIndices, QWidget *parent) : QWidget(parent) {
    setFixedSize(1184, 800);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(1184, 800);
    scene->setSceneRect(0, 0, 1184, 800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QLabel* turnLabel = new QLabel(" Turn: Player 1", this);
    turnLabel->setGeometry(542, 10, 100, 30);
    turnLabel->setStyleSheet("QLabel { color: white; font-size: 16px; background-color: rgba(0, 0, 0, 150); }");

    QPixmap background(":/BoardImage.png");
    if (!background.isNull()) {
        QPixmap scaledBackground = background.scaled(1184, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(scaledBackground);
        backgroundItem->setZValue(-1);
        backgroundItem->setPos(0, 0);
        scene->addItem(backgroundItem);
    } else {
        qDebug() << "Failed to load background image";
    }

    scene->addRect(0, 0, 150, 800, QPen(Qt::NoPen), QBrush(QColor(128, 128, 128, 100)));
    scene->addRect(1034, 0, 150, 800, QPen(Qt::NoPen), QBrush(QColor(128, 128, 128, 100)));

    const int hexCount = 41;
    hexagons_.resize(hexCount);
    setupHexagons();
    initializeNeighbors();

    std::random_device rd;
    std::mt19937 gen(rd());
    loadGrid(":/new/prefix1/grid" + QString::number(std::uniform_int_distribution<>(1, 8)(gen)) + ".txt");

    leftHexagons.resize(8);
    for (size_t i = 0; i < 8; ++i) {
        int idx = leftIndices[i];
        AgentInfo info = agentInfos[idx];
        QString imagePath = boardImagePaths[idx];
        Agent* agent = nullptr;
        DraggableAgent* draggable = nullptr;
        float y = 50 + i * 100;
        QPolygonF hexShape = createHexagon(75, y, 44.5);
        QPointF originalPos = QPointF(75, y);
        switch (info.type) {
        case AgentType::WaterWalking:
            agent = new WaterWalking(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableWaterWalking(hexShape, dynamic_cast<WaterWalking*>(agent), '1', originalPos, this, imagePath);
            break;
        case AgentType::Grounded:
            agent = new Grounded(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableGrounded(hexShape, dynamic_cast<Grounded*>(agent), '1', originalPos, this, imagePath);
            break;
        case AgentType::Flying:
            agent = new Flying(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableFlying(hexShape, dynamic_cast<Flying*>(agent), '1', originalPos, this, imagePath);
            break;
        case AgentType::Floating:
            agent = new Floating(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableFloating(hexShape, dynamic_cast<Floating*>(agent), '1', originalPos, this, imagePath);
            break;
        }
        leftHexagons[i] = draggable;
        scene->addItem(draggable);
    }
    qDebug() << "Left Hexagons Agents:";
    for (const auto* agent : leftHexagons) {
        qDebug() << agent->getAgent()->getName() << static_cast<int>(agent->getAgent()->getAgentType());
    }

    rightHexagons.resize(8);
    for (size_t i = 0; i < 8; ++i) {
        int idx = rightIndices[i];
        AgentInfo info = agentInfos[idx];
        QString imagePath = boardImagePaths[idx];
        Agent* agent = nullptr;
        DraggableAgent* draggable = nullptr;
        float y = 50 + i * 100;
        QPolygonF hexShape = createHexagon(1109, y, 44.5);
        QPointF originalPos = QPointF(1109, y);
        switch (info.type) {
        case AgentType::WaterWalking:
            agent = new WaterWalking(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableWaterWalking(hexShape, dynamic_cast<WaterWalking*>(agent), '2', originalPos, this, imagePath);
            break;
        case AgentType::Grounded:
            agent = new Grounded(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableGrounded(hexShape, dynamic_cast<Grounded*>(agent), '2', originalPos, this, imagePath);
            break;
        case AgentType::Flying:
            agent = new Flying(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableFlying(hexShape, dynamic_cast<Flying*>(agent), '2', originalPos, this, imagePath);
            break;
        case AgentType::Floating:
            agent = new Floating(info.name, info.hp, info.mobility, info.damage, info.attackRange);
            draggable = new DraggableFloating(hexShape, dynamic_cast<Floating*>(agent), '2', originalPos, this, imagePath);
            break;
        }
        rightHexagons[i] = draggable;
        scene->addItem(draggable);
    }
    qDebug() << "Right Hexagons Agents:";
    for (const auto* agent : rightHexagons) {
        qDebug() << agent->getAgent()->getName() << static_cast<int>(agent->getAgent()->getAgentType());
    }

    drawBoard();
    printHexagonInfo();
}

HexGame::~HexGame() {
    for (Hexagon *hex : hexagons_) {
        delete hex;
    }
    for (DraggableAgent *agent : leftHexagons) {
        delete agent;
    }
    for (DraggableAgent *agent : rightHexagons) {
        delete agent;
    }
    delete scene;
    delete view;
}

void HexGame::loadGrid(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Cannot open file:" << filename;
        return;
    }
    QTextStream in(&file);
    QStringList lines = in.readAll().split('\n');
    file.close();

    size_t hexIndex = 0;
    for (qsizetype row = 0; row < lines.size() && hexIndex < hexagons_.size(); ++row) {
        const QString& line = lines[row];
        for (qsizetype col = 0; col < line.length() && hexIndex < hexagons_.size(); ++col) {
            if (line[col] == '/' && col + 1 < line.length()) {
                QChar value = line[col + 1];
                if (value == '~' || value == '#' || value == '1' || value == '2' || value == ' ') {
                    if (value == '1') {
                        hexagons_[hexIndex]->setValue("s1");
                    } else if (value == '2') {
                        hexagons_[hexIndex]->setValue("s2");
                    } else {
                        hexagons_[hexIndex]->setValue(QString(value));
                    }
                    ++hexIndex;
                    ++col;
                }
            }
        }
    }
}

void HexGame::setupHexagons() {
    const qreal verticalSpacing = 43.3;
    const qreal xOffset = 259;
    const qreal yOffset = 170;
    int b = 0;
    for (int var = 0; var <= 4; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset, " ", var);
        b += 150;
    }
    int d = 0;
    for (int var = 5; var <= 8; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + verticalSpacing, " ", var);
        d += 150;
    }
    b = 0;
    for (int var = 9; var <= 13; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 2 * verticalSpacing, " ", var);
        b += 150;
    }
    d = 0;
    for (int var = 14; var <= 17; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + 3 * verticalSpacing, " ", var);
        d += 150;
    }
    b = 0;
    for (int var = 18; var <= 22; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 4 * verticalSpacing, " ", var);
        b += 150;
    }
    d = 0;
    for (int var = 23; var <= 26; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + 5 * verticalSpacing, " ", var);
        d += 150;
    }
    b = 0;
    for (int var = 27; var <= 31; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 6 * verticalSpacing, " ", var);
        b += 150;
    }
    d = 0;
    for (int var = 32; var <= 35; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + 7 * verticalSpacing, " ", var);
        d += 150;
    }
    b = 0;
    for (int var = 36; var <= 40; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 8 * verticalSpacing, " ", var);
        b += 150;
    }
}

void HexGame::initializeNeighbors() {
    hexagons_[0]->setNeighbor(0, hexagons_[5]);
    hexagons_[0]->setNeighbor(1, hexagons_[9]);
    hexagons_[1]->setNeighbor(0, hexagons_[5]);
    hexagons_[1]->setNeighbor(1, hexagons_[10]);
    hexagons_[1]->setNeighbor(2, hexagons_[6]);
    hexagons_[2]->setNeighbor(0, hexagons_[6]);
    hexagons_[2]->setNeighbor(1, hexagons_[11]);
    hexagons_[2]->setNeighbor(2, hexagons_[7]);
    hexagons_[3]->setNeighbor(0, hexagons_[7]);
    hexagons_[3]->setNeighbor(1, hexagons_[12]);
    hexagons_[3]->setNeighbor(2, hexagons_[8]);
    hexagons_[4]->setNeighbor(0, hexagons_[8]);
    hexagons_[4]->setNeighbor(1, hexagons_[13]);
    hexagons_[5]->setNeighbor(0, hexagons_[0]);
    hexagons_[5]->setNeighbor(1, hexagons_[9]);
    hexagons_[5]->setNeighbor(2, hexagons_[14]);
    hexagons_[5]->setNeighbor(3, hexagons_[10]);
    hexagons_[5]->setNeighbor(4, hexagons_[1]);
    hexagons_[6]->setNeighbor(0, hexagons_[1]);
    hexagons_[6]->setNeighbor(1, hexagons_[10]);
    hexagons_[6]->setNeighbor(2, hexagons_[15]);
    hexagons_[6]->setNeighbor(3, hexagons_[11]);
    hexagons_[6]->setNeighbor(4, hexagons_[2]);
    hexagons_[7]->setNeighbor(0, hexagons_[2]);
    hexagons_[7]->setNeighbor(1, hexagons_[11]);
    hexagons_[7]->setNeighbor(2, hexagons_[16]);
    hexagons_[7]->setNeighbor(3, hexagons_[12]);
    hexagons_[7]->setNeighbor(4, hexagons_[3]);
    hexagons_[8]->setNeighbor(0, hexagons_[3]);
    hexagons_[8]->setNeighbor(1, hexagons_[12]);
    hexagons_[8]->setNeighbor(2, hexagons_[17]);
    hexagons_[8]->setNeighbor(3, hexagons_[13]);
    hexagons_[8]->setNeighbor(4, hexagons_[4]);
    hexagons_[9]->setNeighbor(0, hexagons_[0]);
    hexagons_[9]->setNeighbor(1, hexagons_[5]);
    hexagons_[9]->setNeighbor(2, hexagons_[14]);
    hexagons_[9]->setNeighbor(3, hexagons_[18]);
    hexagons_[10]->setNeighbor(0, hexagons_[1]);
    hexagons_[10]->setNeighbor(1, hexagons_[5]);
    hexagons_[10]->setNeighbor(2, hexagons_[14]);
    hexagons_[10]->setNeighbor(3, hexagons_[19]);
    hexagons_[10]->setNeighbor(4, hexagons_[15]);
    hexagons_[10]->setNeighbor(5, hexagons_[6]);
    hexagons_[11]->setNeighbor(0, hexagons_[2]);
    hexagons_[11]->setNeighbor(1, hexagons_[6]);
    hexagons_[11]->setNeighbor(2, hexagons_[15]);
    hexagons_[11]->setNeighbor(3, hexagons_[20]);
    hexagons_[11]->setNeighbor(4, hexagons_[16]);
    hexagons_[11]->setNeighbor(5, hexagons_[7]);
    hexagons_[12]->setNeighbor(0, hexagons_[3]);
    hexagons_[12]->setNeighbor(1, hexagons_[7]);
    hexagons_[12]->setNeighbor(2, hexagons_[16]);
    hexagons_[12]->setNeighbor(3, hexagons_[21]);
    hexagons_[12]->setNeighbor(4, hexagons_[17]);
    hexagons_[12]->setNeighbor(5, hexagons_[8]);
    hexagons_[13]->setNeighbor(0, hexagons_[4]);
    hexagons_[13]->setNeighbor(1, hexagons_[8]);
    hexagons_[13]->setNeighbor(2, hexagons_[17]);
    hexagons_[13]->setNeighbor(3, hexagons_[22]);
    hexagons_[14]->setNeighbor(0, hexagons_[5]);
    hexagons_[14]->setNeighbor(1, hexagons_[9]);
    hexagons_[14]->setNeighbor(2, hexagons_[18]);
    hexagons_[14]->setNeighbor(3, hexagons_[23]);
    hexagons_[14]->setNeighbor(4, hexagons_[19]);
    hexagons_[14]->setNeighbor(5, hexagons_[10]);
    hexagons_[15]->setNeighbor(0, hexagons_[6]);
    hexagons_[15]->setNeighbor(1, hexagons_[10]);
    hexagons_[15]->setNeighbor(2, hexagons_[19]);
    hexagons_[15]->setNeighbor(3, hexagons_[24]);
    hexagons_[15]->setNeighbor(4, hexagons_[20]);
    hexagons_[15]->setNeighbor(5, hexagons_[11]);
    hexagons_[16]->setNeighbor(0, hexagons_[7]);
    hexagons_[16]->setNeighbor(1, hexagons_[11]);
    hexagons_[16]->setNeighbor(2, hexagons_[20]);
    hexagons_[16]->setNeighbor(3, hexagons_[25]);
    hexagons_[16]->setNeighbor(4, hexagons_[21]);
    hexagons_[16]->setNeighbor(5, hexagons_[12]);
    hexagons_[17]->setNeighbor(0, hexagons_[8]);
    hexagons_[17]->setNeighbor(1, hexagons_[12]);
    hexagons_[17]->setNeighbor(2, hexagons_[21]);
    hexagons_[17]->setNeighbor(3, hexagons_[26]);
    hexagons_[17]->setNeighbor(4, hexagons_[22]);
    hexagons_[17]->setNeighbor(5, hexagons_[13]);
    hexagons_[18]->setNeighbor(0, hexagons_[9]);
    hexagons_[18]->setNeighbor(1, hexagons_[14]);
    hexagons_[18]->setNeighbor(2, hexagons_[23]);
    hexagons_[18]->setNeighbor(3, hexagons_[27]);
    hexagons_[19]->setNeighbor(0, hexagons_[10]);
    hexagons_[19]->setNeighbor(1, hexagons_[14]);
    hexagons_[19]->setNeighbor(2, hexagons_[23]);
    hexagons_[19]->setNeighbor(3, hexagons_[28]);
    hexagons_[19]->setNeighbor(4, hexagons_[24]);
    hexagons_[19]->setNeighbor(5, hexagons_[15]);
    hexagons_[20]->setNeighbor(0, hexagons_[11]);
    hexagons_[20]->setNeighbor(1, hexagons_[15]);
    hexagons_[20]->setNeighbor(2, hexagons_[24]);
    hexagons_[20]->setNeighbor(3, hexagons_[29]);
    hexagons_[20]->setNeighbor(4, hexagons_[25]);
    hexagons_[20]->setNeighbor(5, hexagons_[16]);
    hexagons_[21]->setNeighbor(0, hexagons_[12]);
    hexagons_[21]->setNeighbor(1, hexagons_[16]);
    hexagons_[21]->setNeighbor(2, hexagons_[25]);
    hexagons_[21]->setNeighbor(3, hexagons_[30]);
    hexagons_[21]->setNeighbor(4, hexagons_[26]);
    hexagons_[21]->setNeighbor(5, hexagons_[17]);

    hexagons_[22]->setNeighbor(0, hexagons_[13]);
    hexagons_[22]->setNeighbor(1, hexagons_[17]);
    hexagons_[22]->setNeighbor(2, hexagons_[26]);
    hexagons_[22]->setNeighbor(3, hexagons_[31]);
    hexagons_[23]->setNeighbor(0, hexagons_[14]);
    hexagons_[23]->setNeighbor(1, hexagons_[18]);
    hexagons_[23]->setNeighbor(2, hexagons_[27]);
    hexagons_[23]->setNeighbor(3, hexagons_[32]);
    hexagons_[23]->setNeighbor(4, hexagons_[28]);
    hexagons_[23]->setNeighbor(5, hexagons_[19]);
    hexagons_[24]->setNeighbor(0, hexagons_[15]);
    hexagons_[24]->setNeighbor(1, hexagons_[19]);
    hexagons_[24]->setNeighbor(2, hexagons_[28]);
    hexagons_[24]->setNeighbor(3, hexagons_[33]);
    hexagons_[24]->setNeighbor(4, hexagons_[29]);
    hexagons_[24]->setNeighbor(5, hexagons_[20]);
    hexagons_[25]->setNeighbor(0, hexagons_[16]);
    hexagons_[25]->setNeighbor(1, hexagons_[20]);
    hexagons_[25]->setNeighbor(2, hexagons_[29]);
    hexagons_[25]->setNeighbor(3, hexagons_[34]);
    hexagons_[25]->setNeighbor(4, hexagons_[30]);
    hexagons_[25]->setNeighbor(5, hexagons_[21]);
    hexagons_[26]->setNeighbor(0, hexagons_[17]);
    hexagons_[26]->setNeighbor(1, hexagons_[21]);
    hexagons_[26]->setNeighbor(2, hexagons_[30]);
    hexagons_[26]->setNeighbor(3, hexagons_[35]);
    hexagons_[26]->setNeighbor(4, hexagons_[31]);
    hexagons_[26]->setNeighbor(5, hexagons_[22]);
    hexagons_[27]->setNeighbor(0, hexagons_[18]);
    hexagons_[27]->setNeighbor(1, hexagons_[23]);
    hexagons_[27]->setNeighbor(2, hexagons_[32]);
    hexagons_[27]->setNeighbor(3, hexagons_[36]);
    hexagons_[28]->setNeighbor(0, hexagons_[19]);
    hexagons_[28]->setNeighbor(1, hexagons_[23]);
    hexagons_[28]->setNeighbor(2, hexagons_[32]);
    hexagons_[28]->setNeighbor(3, hexagons_[37]);
    hexagons_[28]->setNeighbor(4, hexagons_[33]);
    hexagons_[28]->setNeighbor(5, hexagons_[24]);
    hexagons_[29]->setNeighbor(0, hexagons_[20]);
    hexagons_[29]->setNeighbor(1, hexagons_[24]);
    hexagons_[29]->setNeighbor(2, hexagons_[33]);
    hexagons_[29]->setNeighbor(3, hexagons_[38]);
    hexagons_[29]->setNeighbor(4, hexagons_[34]);
    hexagons_[29]->setNeighbor(5, hexagons_[25]);
    hexagons_[30]->setNeighbor(0, hexagons_[21]);
    hexagons_[30]->setNeighbor(1, hexagons_[25]);
    hexagons_[30]->setNeighbor(2, hexagons_[34]);
    hexagons_[30]->setNeighbor(3, hexagons_[39]);
    hexagons_[30]->setNeighbor(4, hexagons_[35]);
    hexagons_[30]->setNeighbor(5, hexagons_[26]);
    hexagons_[31]->setNeighbor(0, hexagons_[22]);
    hexagons_[31]->setNeighbor(1, hexagons_[26]);
    hexagons_[31]->setNeighbor(2, hexagons_[35]);
    hexagons_[31]->setNeighbor(3, hexagons_[40]);
    hexagons_[32]->setNeighbor(0, hexagons_[23]);
    hexagons_[32]->setNeighbor(1, hexagons_[27]);
    hexagons_[32]->setNeighbor(2, hexagons_[36]);
    hexagons_[32]->setNeighbor(3, hexagons_[37]);
    hexagons_[32]->setNeighbor(4, hexagons_[28]);
    hexagons_[33]->setNeighbor(0, hexagons_[24]);
    hexagons_[33]->setNeighbor(1, hexagons_[28]);
    hexagons_[33]->setNeighbor(2, hexagons_[37]);
    hexagons_[33]->setNeighbor(3, hexagons_[38]);
    hexagons_[33]->setNeighbor(4, hexagons_[29]);
    hexagons_[34]->setNeighbor(0, hexagons_[25]);
    hexagons_[34]->setNeighbor(1, hexagons_[29]);
    hexagons_[34]->setNeighbor(2, hexagons_[38]);
    hexagons_[34]->setNeighbor(3, hexagons_[39]);
    hexagons_[34]->setNeighbor(4, hexagons_[30]);
    hexagons_[35]->setNeighbor(0, hexagons_[26]);
    hexagons_[35]->setNeighbor(1, hexagons_[30]);
    hexagons_[35]->setNeighbor(2, hexagons_[39]);
    hexagons_[35]->setNeighbor(3, hexagons_[40]);
    hexagons_[35]->setNeighbor(4, hexagons_[31]);
    hexagons_[36]->setNeighbor(0, hexagons_[27]);
    hexagons_[36]->setNeighbor(1, hexagons_[32]);
    hexagons_[37]->setNeighbor(0, hexagons_[32]);
    hexagons_[37]->setNeighbor(1, hexagons_[28]);
    hexagons_[37]->setNeighbor(2, hexagons_[33]);
    hexagons_[38]->setNeighbor(0, hexagons_[33]);
    hexagons_[38]->setNeighbor(1, hexagons_[29]);
    hexagons_[38]->setNeighbor(2, hexagons_[34]);
    hexagons_[39]->setNeighbor(0, hexagons_[34]);
    hexagons_[39]->setNeighbor(1, hexagons_[30]);
    hexagons_[39]->setNeighbor(2, hexagons_[35]);
    hexagons_[40]->setNeighbor(0, hexagons_[35]);
    hexagons_[40]->setNeighbor(1, hexagons_[31]);
}

void HexGame::printHexagonInfo() {
    std::vector<std::vector<int>> rows = {
        {0, 1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12, 13},
        {14, 15, 16, 17},
        {18, 19, 20, 21, 22},
        {23, 24, 25, 26},
        {27, 28, 29, 30, 31},
        {32, 33, 34, 35},
        {36, 37, 38, 39, 40}
    };

    for (size_t row = 0; row < rows.size(); ++row) {
        qDebug() << "Row" << (row + 1) << ":";
        for (int hexIndex : rows[row]) {
            QString value = hexagons_[hexIndex]->getValue();
            QString neighbors;
            for (int i = 0; i < 6; ++i) {
                Hexagon* neighbor = hexagons_[hexIndex]->getNeighbor(i);
                if (neighbor) {
                    neighbors += QString("(%1: %2) ").arg(neighbor->getIndex()).arg(neighbor->getValue());
                }
            }
            qDebug().noquote() << QString("Hex %1: Value = %2, Neighbors = %3").arg(hexIndex).arg(value).arg(neighbors);
        }
    }
}

QPolygonF HexGame::createHexagon(qreal x, qreal y, qreal radius) const {
    QPolygonF hexagon;
    qreal adjustedRadius = radius > 0 ? radius : 50;
    for (int i = 0; i < 6; ++i) {
        qreal angle = M_PI / 3.0 * i;
        hexagon << QPointF(x + adjustedRadius * cos(angle), y + adjustedRadius * sin(angle));
    }
    return hexagon;
}

Hexagon* HexGame::findNearestCell(const QPointF& pos, qreal& minDistance) {
    Hexagon* nearest = nullptr;
    minDistance = std::numeric_limits<qreal>::max();

    for (Hexagon* hex : hexagons_) {
        QPointF center = hex->getCenter();
        qreal distance = std::hypot(pos.x() - center.x(), pos.y() - center.y());
        if (distance < minDistance) {
            minDistance = distance;
            nearest = hex;
        }
    }
    return nearest;
}

void HexGame::drawBoard() {
    QList<QGraphicsItem*> itemsToKeep;
    for (DraggableAgent* agent : leftHexagons) {
        itemsToKeep << agent;
    }
    for (DraggableAgent* agent : rightHexagons) {
        itemsToKeep << agent;
    }
    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == QGraphicsRectItem::Type ||
            item->type() == QGraphicsPixmapItem::Type ||
            itemsToKeep.contains(item)) {
            continue;
        }
        scene->removeItem(item);
        delete item;
    }

    for (Hexagon* hex : hexagons_) {
        QString value = hex->getValue();
        QPointF center = hex->getCenter();
        QPolygonF hexShape = createHexagon(center.x(), center.y(), 50);
        QGraphicsPolygonItem* hexItem = new QGraphicsPolygonItem(hexShape);

        if (value == "s1") {
            hexItem->setBrush(QColor(61, 59, 243));
        } else if (value == "s2") {
            hexItem->setBrush(QColor(217, 22, 86));
        } else if (value == "#") {
            hexItem->setBrush(QColor(240, 187, 120));
        } else if (value == "~") {
            hexItem->setBrush(QColor(96, 181, 255));
        } else {
            hexItem->setBrush(QColor("white"));
        }
        hexItem->setPen(QPen(Qt::black, 2));
        hexItem->setZValue(0);
        scene->addItem(hexItem);
    }

    view->show();
}

std::pair<std::vector<Hexagon*>, std::vector<DraggableAgent*>> HexGame::bfs(Hexagon* start, AgentType type, int mobility, int attackRange) {
    std::vector<Hexagon*> moveResult;
    std::vector<DraggableAgent*> attackableEnemies;
    std::queue<std::pair<Hexagon*, int>> queue;
    std::set<Hexagon*> visited;

    DraggableAgent* currentAgent = nullptr;
    for (DraggableAgent* da : leftHexagons) {
        if (da->getAgent()->getPosition() == start) {
            currentAgent = da;
            break;
        }
    }
    if (!currentAgent) {
        for (DraggableAgent* da : rightHexagons) {
            if (da->getAgent()->getPosition() == start) {
                currentAgent = da;
                break;
            }
        }
    }
    if (!currentAgent) {
        return {moveResult, attackableEnemies};
    }
    QChar currentPlayer = currentAgent->getPlayer();

    for (int i = 0; i < 6; ++i) {
        Hexagon* neighbor = start->getNeighbor(i);
        if (neighbor && visited.find(neighbor) == visited.end()) {
            bool isValidMove = true;
            bool isValidLanding = true;
            QString cellValue = neighbor->getValue();

            if (type == AgentType::WaterWalking) {
                if (cellValue == "#") isValidMove = isValidLanding = false;
            } else if (type == AgentType::Grounded) {
                if (cellValue == "~" || cellValue == "#") isValidMove = isValidLanding = false;
            } else if (type == AgentType::Floating) {

            } else if (type == AgentType::Flying) {
                if (cellValue == "#" || cellValue == "~") isValidLanding = false;
            }

            bool isOccupied = false;
            for (DraggableAgent* da : leftHexagons) {
                if (da->getAgent()->getPosition() == neighbor) {
                    isOccupied = true;
                    if (da->getPlayer() != currentPlayer && attackRange >= 1) {
                        attackableEnemies.push_back(da);
                    }
                }
            }
            for (DraggableAgent* da : rightHexagons) {
                if (da->getAgent()->getPosition() == neighbor) {
                    isOccupied = true;
                    if (da->getPlayer() != currentPlayer && attackRange >= 1) {
                        attackableEnemies.push_back(da);
                    }
                }
            }

            if (isValidMove && !isOccupied) {
                visited.insert(neighbor);
                queue.push({neighbor, 1});
                if (isValidLanding) {
                    moveResult.push_back(neighbor);
                }
            }
        }
    }

    while (!queue.empty()) {
        auto [current, distance] = queue.front();
        queue.pop();

        if (distance < std::max(mobility, attackRange)) {
            for (int i = 0; i < 6; ++i) {
                Hexagon* neighbor = current->getNeighbor(i);
                if (neighbor && visited.find(neighbor) == visited.end() && neighbor != start) {
                    bool isValidMove = true;
                    bool isValidLanding = true;
                    QString cellValue = neighbor->getValue();

                    if (type == AgentType::WaterWalking) {
                        if (cellValue == "#") isValidMove = isValidLanding = false;
                    } else if (type == AgentType::Grounded) {
                        if (cellValue == "~" || cellValue == "#") isValidMove = isValidLanding = false;
                    } else if (type == AgentType::Floating) {
                    } else if (type == AgentType::Flying) {
                        if (cellValue == "#" || cellValue == "~") isValidLanding = false;
                    }

                    bool isOccupied = false;
                    for (DraggableAgent* da : leftHexagons) {
                        if (da->getAgent()->getPosition() == neighbor) {
                            isOccupied = true;
                            if (da->getPlayer() != currentPlayer && distance + 1 <= attackRange) {
                                attackableEnemies.push_back(da);
                            }
                        }
                    }
                    for (DraggableAgent* da : rightHexagons) {
                        if (da->getAgent()->getPosition() == neighbor) {
                            isOccupied = true;
                            if (da->getPlayer() != currentPlayer && distance + 1 <= attackRange) {
                                attackableEnemies.push_back(da);
                            }
                        }
                    }

                    if (isValidMove && !isOccupied) {
                        visited.insert(neighbor);
                        queue.push({neighbor, distance + 1});
                        if (distance + 1 <= mobility && isValidLanding) {
                            moveResult.push_back(neighbor);
                        }
                    }
                }
            }
        }
    }

    std::vector<Hexagon*> uniqueMoveResult;
    std::set<Hexagon*> seen;
    for (Hexagon* hex : moveResult) {
        if (seen.find(hex) == seen.end()) {
            seen.insert(hex);
            uniqueMoveResult.push_back(hex);
        }
    }

    std::vector<DraggableAgent*> uniqueAttackableEnemies;
    std::set<DraggableAgent*> seenAgents;
    for (DraggableAgent* agent : attackableEnemies) {
        if (seenAgents.find(agent) == seenAgents.end()) {
            seenAgents.insert(agent);
            uniqueAttackableEnemies.push_back(agent);
        }
    }

    return {uniqueMoveResult, uniqueAttackableEnemies};
}
void HexGame::highlightPath(const std::vector<Hexagon*>& path, const std::vector<DraggableAgent*>& attackableEnemies) {
    clearHighlight();
    for (Hexagon* hex : path) {
        QPointF center = hex->getCenter();
        QPolygonF hexShape = createHexagon(center.x(), center.y(), 50);
        QGraphicsPolygonItem* hexItem = new QGraphicsPolygonItem(hexShape);
        hexItem->setBrush(QColor(0, 255, 0, 150));
        hexItem->setPen(QPen(Qt::black, 2));
        hexItem->setZValue(5);
        scene->addItem(hexItem);
    }
    for (DraggableAgent* enemy : attackableEnemies) {
        QPolygonF enemyShape = enemy->polygon();
        QGraphicsPolygonItem* enemyItem = new QGraphicsPolygonItem(enemyShape);
        enemyItem->setPos(enemy->pos());
        enemyItem->setBrush(QColor(255, 0, 0, 200));
        enemyItem->setPen(QPen(Qt::black, 2));
        enemyItem->setZValue(15);
        scene->addItem(enemyItem);
    }
    view->update();
}

void HexGame::clearHighlight() {
    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == QGraphicsPolygonItem::Type &&
            (item->zValue() == 5 || item->zValue() == 15)) {
            scene->removeItem(item);
            delete item;
        }
    }
}

void HexGame::setCurrentHighlightedAgent(DraggableAgent* agent) {
    currentHighlightedAgent = agent;
}

DraggableAgent* HexGame::getCurrentHighlightedAgent() const {
    return currentHighlightedAgent;
}
void HexGame::switchTurn() {
    currentPlayer_ = (currentPlayer_ == '1') ? '2' : '1';
    actionsTaken_ = 0;
    qDebug() << "Turn switched to Player" << currentPlayer_;
    clearHighlight();
    setCurrentHighlightedAgent(nullptr);
    drawBoard();
    QLabel* turnLabel = findChild<QLabel*>();
    if (turnLabel) {
        turnLabel->setText(QString(" Turn: Player %1").arg(currentPlayer_));
    }
}
int HexGame::countAgentsOnBoard(QChar player) const {
    int count = 0;
    const std::vector<DraggableAgent*>& playerHexagons = (player == '1') ? leftHexagons : rightHexagons;
    for (const auto* agent : playerHexagons) {
        if (agent->getAgent()->getPosition() != nullptr) {
            count++;
        }
    }
    return count;
}
