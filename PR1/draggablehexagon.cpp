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
        setBrush(QColor(213, 11, 139));
    }
    setPen(QPen(QColor(139, 69, 19), 1));
}

void DraggableHexagon::mousePressEvent(QGraphicsSceneMouseEvent* event) {
        if (event->button() == Qt::LeftButton) {
            setZValue(20);
            qreal minDistance;
            Hexagon* nearestCell = game->findNearestCell(pos() + boundingRect().center(), minDistance);
            if (nearestCell && minDistance < 100) {
                if (!isHighlighted) {
                    std::vector<Hexagon*> path = game->bfs(nearestCell, type);
                    game->highlightPath(path);
                    isHighlighted = true;
                } else {
                    game->clearHighlight();
                    isHighlighted = false;
                }
            }
        }
        QGraphicsPolygonItem::mousePressEvent(event);
    }

void DraggableHexagon::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(20);
    setPos(event->scenePos() - event->buttonDownPos(Qt::LeftButton));
    game->clearHighlight();
}

void DraggableHexagon::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    qreal minDistance;
    Hexagon* nearestCell = game->findNearestCell(event->scenePos(), minDistance);

    if (nearestCell && minDistance < 100) {
        setPos(nearestCell->getCenter() - boundingRect().center());
        originalPos = nearestCell->getCenter();
    } else {
        setPos(originalPos - boundingRect().center());
    }
    setZValue(10);
    QGraphicsPolygonItem::mouseReleaseEvent(event);
    }
