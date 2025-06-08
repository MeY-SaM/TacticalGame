#include "draggablehexagon.h"
#include "hexgame.h"
#include <QDebug>

DraggableHexagon::DraggableHexagon(const QPolygonF& polygon, QChar t, const QPointF& origPos, HexGame* g)
    : QGraphicsPolygonItem(polygon), type(t), originalPos(origPos), game(g) {
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setZValue(10);
    if (type == '1') {
        setBrush(QColor(224, 174, 208));
    } else if (type == '2') {
        setBrush(QColor(221, 168, 83));
    }
    setPen(QPen(QColor(139, 69, 19), 1));
}

void DraggableHexagon::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(20);
    QGraphicsPolygonItem::mousePressEvent(event);
}

void DraggableHexagon::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(20);
    setPos(event->scenePos() - event->buttonDownPos(Qt::LeftButton));
}

void DraggableHexagon::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    qreal minDistance;
    Hexagon* nearestCell = game->findNearestCell(event->scenePos(), minDistance);

    if (nearestCell && minDistance < 100) {
        setPos(nearestCell->getCenter() - boundingRect().center());
        originalPos = nearestCell->getCenter();
        game->drawBoard();
    } else {
        setPos(originalPos - boundingRect().center());
    }
    setZValue(10);
    QGraphicsPolygonItem::mouseReleaseEvent(event);
}
