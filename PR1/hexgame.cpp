#include "hexgame.h"
#include <QApplication>
#include <QDebug>
#include <cmath>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QLabel>
#include <QRandomGenerator>

HexGame::HexGame(QWidget *parent) : QWidget(parent), leftHex(nullptr), rightHex(nullptr) {
    setFixedSize(1184, 800);
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setFixedSize(1184, 800);
    scene->setSceneRect(0, 0, 1184, 800);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap background(":/BoardImage.png");
    if (!background.isNull()) {
        QPixmap scaledBackground = background.scaled(1184, 800, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem *backgroundItem = new QGraphicsPixmapItem(scaledBackground);
        backgroundItem->setZValue(-1);
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

    int randomNum = QRandomGenerator::global()->bounded(1, 9);
    QString gridFile = QString(":/new/prefix1/grid%1.txt").arg(randomNum);
    loadGrid(gridFile);

    QPolygonF hexShape = createHexagon(75, 336, 50);
    leftHex = new DraggableHexagon(hexShape, '1', QPointF(75, 336), this);
    scene->addItem(leftHex);

    hexShape = createHexagon(1109, 336, 50);
    rightHex = new DraggableHexagon(hexShape, '2', QPointF(1109, 336), this);
    scene->addItem(rightHex);

    drawBoard();

    printHexagonInfo();
}

HexGame::~HexGame() {
    for (Hexagon *hex : hexagons_) {
        delete hex;
    }
    delete leftHex;
    delete rightHex;
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

    int hexIndex = 0;
    for (int row = 0; row < lines.size() - 1 && hexIndex < hexagons_.size(); ++row) {
        const QString& line = lines[row];
        for (int col = 0; col < line.length() && hexIndex < hexagons_.size(); ++col) {
            if (line[col] == '/' && col + 1 < line.length()) {
                QChar value = line[col + 1];
                if (value == '~' || value == '#' || value == '1' || value == '2' || value == ' ') {
                    hexagons_[hexIndex]->setValue(value);
                    ++hexIndex;
                    ++col;
                }
            }
        }
    }
}

void HexGame::setupHexagons() {
    const int hexCount = 41;
    const qreal verticalSpacing = 43.3;
    const qreal xOffset = 259;
    const qreal yOffset = 170;
    int b = 0;
    for (int var = 0; var <= 4; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset, ' ', var);
        b += 150;
    }
    int d = 0;
    for (int var = 5; var <= 8; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + verticalSpacing, ' ', var);
        d += 150;
    }
    b = 0;
    for (int var = 9; var <= 13; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 2 * verticalSpacing, ' ', var);
        b += 150;
    }
    d = 0;
    for (int var = 14; var <= 17; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + 3 * verticalSpacing, ' ', var);
        d += 150;
    }
    b = 0;
    for (int var = 18; var <= 22; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 4 * verticalSpacing, ' ', var);
        b += 150;
    }
    d = 0;
    for (int var = 23; var <= 26; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + 5 * verticalSpacing, ' ', var);
        d += 150;
    }
    b = 0;
    for (int var = 27; var <= 31; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 6 * verticalSpacing, ' ', var);
        b += 150;
    }
    d = 0;
    for (int var = 32; var <= 35; ++var) {
        hexagons_[var] = new Hexagon(xOffset + 75 + d, yOffset + 7 * verticalSpacing, ' ', var);
        d += 150;
    }
    b = 0;
    for (int var = 36; var <= 40; ++var) {
        hexagons_[var] = new Hexagon(xOffset + b, yOffset + 8 * verticalSpacing, ' ', var);
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
    hexagons_[19]->setNeighbor(5, hexagons_[11]);
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
            QChar value = hexagons_[hexIndex]->getValue();
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
    itemsToKeep << leftHex << rightHex;
    for (QGraphicsItem* item : scene->items()) {
        if (item->type() == QGraphicsRectItem::Type || item->type() == QGraphicsPixmapItem::Type || itemsToKeep.contains(item)) {
            continue;
        }
        scene->removeItem(item);
        delete item;
    }

    for (Hexagon* hex : hexagons_) {
        QChar value = hex->getValue();
        QPointF center = hex->getCenter();
        QPolygonF hexShape = createHexagon(center.x(), center.y(), 50);
        QGraphicsPolygonItem* hexItem = new QGraphicsPolygonItem(hexShape);

        if (value == '1') {
            hexItem->setBrush(QColor(61, 59, 243));
        } else if (value == '2') {
            hexItem->setBrush(QColor(217, 22, 86));
        } else if (value == '#') {
            hexItem->setBrush(QColor(240, 187, 120));
        } else if (value == '~') {
            hexItem->setBrush(QColor(96, 181, 255));
        } else {
            hexItem->setBrush(QColor("white"));
        }
        hexItem->setPen(QPen(Qt::black, 10));
        hexItem->setZValue(0);
        scene->addItem(hexItem);
    }

    view->show();
}
