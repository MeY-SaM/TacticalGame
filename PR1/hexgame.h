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
#include <QGraphicsSceneMouseEvent>
#include <cmath>
#include <QDebug>

#include "hexagon.h"
#include "agent.h"

class DraggableAgent;

class HexGame : public QWidget {
    Q_OBJECT

public:
    explicit HexGame(QWidget *parent = nullptr);
    ~HexGame();

    void printHexagonInfo();
    Hexagon* findNearestCell(const QPointF& pos, qreal& minDistance);
    QPolygonF createHexagon(qreal x, qreal y, qreal radius) const;
    void drawBoard();
    std::vector<Hexagon*> bfs(Hexagon* start, AgentType type, int mobility);
    void highlightPath(const std::vector<Hexagon*>& path);
    void clearHighlight();

private:
    void loadGrid(const QString &filename);
    void setupHexagons();
    void initializeNeighbors();

    std::vector<Hexagon*> hexagons_;
    QGraphicsScene* scene;
    QGraphicsView* view;
    std::vector<DraggableAgent*> leftHexagons;
    std::vector<DraggableAgent*> rightHexagons;
};

#endif // HEXGAME_H
