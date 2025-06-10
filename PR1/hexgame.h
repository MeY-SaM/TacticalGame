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
#include "draggablehexagon.h"

class HexGame : public QWidget {
    Q_OBJECT
public:
    explicit HexGame(QWidget *parent = nullptr);
    ~HexGame();

    void printHexagonInfo();
    Hexagon* findNearestCell(const QPointF& pos, qreal& minDistance);
    QPolygonF createHexagon(qreal x, qreal y, qreal radius) const;
    void drawBoard();
    std::vector<Hexagon*> bfs(Hexagon* start, QChar type);
    void highlightPath(const std::vector<Hexagon*>& path);
    void clearHighlight();

private:
    void loadGrid(const QString &filename);
    void setupHexagons();
    void initializeNeighbors();

    std::vector<Hexagon*> hexagons_;
    QGraphicsScene* scene;
    QGraphicsView* view;
    std::vector<DraggableHexagon*> leftHexagons;
    std::vector<DraggableHexagon*> rightHexagons;
};

#endif // HEXGAME_H
