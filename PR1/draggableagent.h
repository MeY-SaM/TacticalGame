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
    DraggableAgent(const QPolygonF& polygon, Agent* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath);
    ~DraggableAgent();

    Agent* getAgent() const { return agent_; }
    QChar getPlayer() const { return player_; }
    void setOriginalPos(const QPointF& pos) { originalPos_ = pos; }
    void setHighlighted(bool highlighted) { isHighlighted_ = highlighted; }
    void clearHighlightedPath() { highlightedPath_.clear(); }
    void clearHighlightedAttackables() { highlightedAttackables_.clear(); }
    void setHighlightedPath(const std::vector<Hexagon*>& path) { highlightedPath_ = path; }
    void setHighlightedAttackables(const std::vector<DraggableAgent*>& attackables) { highlightedAttackables_ = attackables; }
    const std::vector<Hexagon*>& getHighlightedPath() const { return highlightedPath_; }
    const std::vector<DraggableAgent*>& getHighlightedAttackables() const { return highlightedAttackables_; }

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
    std::vector<DraggableAgent*> highlightedAttackables_;
};

class DraggableWaterWalking : public DraggableAgent {
public:
    DraggableWaterWalking(const QPolygonF& polygon, WaterWalking* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath)
        : DraggableAgent(polygon, agent, player, originalPos, game, imagePath) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setZValue(10);
    }
};

class DraggableGrounded : public DraggableAgent {
public:
    DraggableGrounded(const QPolygonF& polygon, Grounded* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath)
        : DraggableAgent(polygon, agent, player, originalPos, game, imagePath) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setZValue(10);
    }
};

class DraggableFlying : public DraggableAgent {
public:
    DraggableFlying(const QPolygonF& polygon, Flying* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath)
        : DraggableAgent(polygon, agent, player, originalPos, game, imagePath) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setZValue(10);
    }
};

class DraggableFloating : public DraggableAgent {
public:
    DraggableFloating(const QPolygonF& polygon, Floating* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath)
        : DraggableAgent(polygon, agent, player, originalPos, game, imagePath) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
        setZValue(10);
    }
};

#endif
