#ifndef HEXGAME_H
#define HEXGAME_H

#include <QWidget>
#include <QPolygonF>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <vector>
#include <QString>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPolygonItem>
#include <QGraphicsTextItem>
#include <cmath>
#include "hexagon.h"


class HexGame : public QWidget {
    Q_OBJECT
public:
    explicit HexGame(QWidget *parent = nullptr);
    ~HexGame();

    void printHexagonInfo();
    Hexagon* findNearestCell(const QPointF& pos, qreal& minDistance);
    QPolygonF createHexagon(qreal x, qreal y, qreal radius) const;
    void drawBoard();

private:
    void loadGrid(const QString &filename);
    void setupHexagons();
    void initializeNeighbors();

    std::vector<Hexagon*> hexagons_;
    QGraphicsScene* scene;
    QGraphicsView* view;
    DraggableHexagon* leftHex;
    DraggableHexagon* rightHex;
};

#endif // HEXGAME_H
