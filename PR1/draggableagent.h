#ifndef DRAGGABLEAGENT_H
#define DRAGGABLEAGENT_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QChar>
#include "agent.h"

class HexGame;

class DraggableAgent : public QGraphicsPolygonItem {
public:
    DraggableAgent(const QPolygonF& polygon, Agent* agent, QChar player, const QPointF& originalPos, HexGame* game);
    ~DraggableAgent();

    Agent* getAgent() const { return agent_; }
    QChar getPlayer() const { return player_; }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

private:
    Agent* agent_;
    QChar player_;
    QPointF originalPos_;
    HexGame* game_;
    bool isHighlighted_;
    std::vector<Hexagon*> highlightedPath_;
};

class DraggableWaterWalking : public DraggableAgent {
public:
    DraggableWaterWalking(const QPolygonF& polygon, WaterWalking* agent, QChar player, const QPointF& originalPos, HexGame* game)
        : DraggableAgent(polygon, agent, player, originalPos, game) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setZValue(10);
    }
};

#endif // DRAGGABLEAGENT_H
