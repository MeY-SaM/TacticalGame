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
    HexGame(const std::vector<int>& leftIndices, const std::vector<int>& rightIndices, QWidget *parent = nullptr);
    ~HexGame();

    void printHexagonInfo();
    Hexagon* findNearestCell(const QPointF& pos, qreal& minDistance);
    QPolygonF createHexagon(qreal x, qreal y, qreal radius) const;
    void drawBoard();
    std::pair<std::vector<Hexagon*>, std::vector<DraggableAgent*>> bfs(Hexagon* start, AgentType type, int mobility, int attackRange);
    void highlightPath(const std::vector<Hexagon*>& path, const std::vector<DraggableAgent*>& attackableEnemies = {});
    void clearHighlight();
    void setCurrentHighlightedAgent(DraggableAgent* agent);
    DraggableAgent* getCurrentHighlightedAgent() const;
    void performAttack(DraggableAgent* attacker, DraggableAgent* defender);
    void highlightAgentPosition(DraggableAgent* agent);
    void toggleAgentHighlight(DraggableAgent* agent);

private:
    void loadGrid(const QString &filename);
    void setupHexagons();
    void initializeNeighbors();

    std::vector<Hexagon*> hexagons_;
    QGraphicsScene* scene;
    QGraphicsView* view;
    std::vector<DraggableAgent*> leftHexagons;
    std::vector<DraggableAgent*> rightHexagons;
    DraggableAgent* currentHighlightedAgent = nullptr;
    bool isAgentHighlighted = false;
};

#endif
