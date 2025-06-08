#ifndef DRAGGABLEHEXAGON_H
#define DRAGGABLEHEXAGON_H

#include <QGraphicsPolygonItem>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include <QChar>
#include "hexagon.h"

// Forward declaration of HexGame to avoid circular dependency
class HexGame;

class DraggableHexagon : public QGraphicsPolygonItem {
public:
    DraggableHexagon(const QPolygonF& polygon, QChar type, const QPointF& originalPos, HexGame* game);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
private:
    QChar type;
    QPointF originalPos;
    HexGame* game;
};

#endif // DRAGGABLEHEXAGON_H
