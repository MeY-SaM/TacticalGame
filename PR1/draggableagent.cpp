#include "draggableagent.h"
#include "hexgame.h"
#include <QDebug>
#include <algorithm>

DraggableAgent::DraggableAgent(const QPolygonF& polygon, Agent* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath)
    : QGraphicsPolygonItem(polygon), agent_(agent), player_(player), originalPos_(originalPos), game_(game), isHighlighted_(false) {
    if (player == '1') {
        setBrush(QColor(61, 59, 243));
        setPen(Qt::NoPen);
    } else if (player == '2') {
        setBrush(QColor(217, 22, 86));
        setPen(Qt::NoPen);
    }

    setFlag(QGraphicsItem::ItemIsMovable, true);
    setZValue(10);

    QPixmap pixmap(imagePath);
    if (!pixmap.isNull()) {
        QPixmap scaledPixmap = pixmap.scaled(160, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QGraphicsPixmapItem* imageItem = new QGraphicsPixmapItem(scaledPixmap, this);
        imageItem->setPos(boundingRect().center() - QPointF(scaledPixmap.width()/2 + 4, scaledPixmap.height()/2 - 8));
        imageItem->setZValue(11);
    } else {
        qDebug() << "Failed to load image:" << imagePath;
    }
}

DraggableAgent::~DraggableAgent() {
    delete agent_;
}

void DraggableAgent::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        DraggableAgent* attacker = game_->getCurrentHighlightedAgent();
        if (attacker && attacker != this && attacker->getPlayer() != player_) {
            auto it = std::find(attacker->getHighlightedAttackables().begin(), attacker->getHighlightedAttackables().end(), this);
            if (it != attacker->getHighlightedAttackables().end()) {
                attacker->getAgent()->attack(this, game_);
                attacker->setHighlighted(false);
                attacker->clearHighlightedPath();
                attacker->clearHighlightedAttackables();
                game_->clearHighlight();
                game_->setCurrentHighlightedAgent(nullptr);
                return;
            }
        }

        setZValue(20);
        qreal minDistance;
        Hexagon* nearestCell = game_->findNearestCell(pos() + boundingRect().center(), minDistance);
        if (nearestCell && minDistance < 100) {
            if (!isHighlighted_) {
                agent_->move(game_);
                setHighlighted(true);
                game_->setCurrentHighlightedAgent(this);
            } else {
                game_->clearHighlight();
                setHighlighted(false);
                clearHighlightedPath();
                clearHighlightedAttackables();
                game_->setCurrentHighlightedAgent(nullptr);
            }
        }
    }
    QGraphicsPolygonItem::mousePressEvent(event);
}

void DraggableAgent::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    setZValue(20);
    setPos(event->scenePos() - event->buttonDownPos(Qt::LeftButton));
    game_->clearHighlight();
}

void DraggableAgent::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    qreal minDistance;
    Hexagon* nearestCell = game_->findNearestCell(event->scenePos(), minDistance);
    bool isValidPlacement = false;

    if (nearestCell && minDistance < 160) {
        QString cellValue = nearestCell->getValue();
        bool isValidCell = true;

        bool isInitialPlacement = (player_ == '1' && qAbs(originalPos_.x() - 75) < 1) ||
                                  (player_ == '2' && qAbs(originalPos_.x() - 1109) < 1);

        if (isInitialPlacement) {
            if ((player_ == '1' && cellValue == "s1") || (player_ == '2' && cellValue == "s2")) {
                isValidPlacement = true;
            }
        } else {
            if (agent_->getAgentType() == AgentType::WaterWalking) {
                if (cellValue == "#") isValidCell = false;
            } else if (agent_->getAgentType() == AgentType::Grounded) {
                if (cellValue == "~" || cellValue == "#") isValidCell = false;
            } else if (agent_->getAgentType() == AgentType::Floating) {
                // Floating agents can land on any cell
            } else if (agent_->getAgentType() == AgentType::Flying) {
                if (cellValue == "#" || cellValue == "~") isValidCell = false;
            }

            if (cellValue == "1" || cellValue == "2") {
                isValidCell = false;
            }

            isValidPlacement = (isValidCell && std::find(highlightedPath_.begin(), highlightedPath_.end(), nearestCell) != highlightedPath_.end());
        }

        if (isValidPlacement) {
            setPos(nearestCell->getCenter() - boundingRect().center());
            setOriginalPos(nearestCell->getCenter());
            agent_->setPosition(nearestCell);
            game_->drawBoard();
            game_->clearHighlight();
            setHighlighted(false);
            clearHighlightedPath();
            clearHighlightedAttackables();
            game_->setCurrentHighlightedAgent(nullptr);
        } else {
            setPos(originalPos_ - boundingRect().center());
        }
    } else {
        setPos(originalPos_ - boundingRect().center());
    }
    setZValue(10);
    QGraphicsPolygonItem::mouseReleaseEvent(event);
}
