#include "draggableagent.h"
#include "hexgame.h"
#include <QDebug>
#include <algorithm>

DraggableAgent::DraggableAgent(const QPolygonF& polygon, Agent* agent, QChar player, const QPointF& originalPos, HexGame* game, const QString& imagePath)
    : QGraphicsPolygonItem(polygon), agent_(agent), player_(player), originalPos_(originalPos), game_(game), isHighlighted_(false) {
    if (player == '1') {
        setBrush(QColor(224, 174, 208));
    } else if (player == '2') {
        setBrush(QColor(221, 168, 83));
    }
    setPen(QPen(QColor(139, 69, 19), 1));
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
            auto it = std::find(attacker->highlightedAttackables_.begin(), attacker->highlightedAttackables_.end(), this);
            if (it != attacker->highlightedAttackables_.end()) {
                game_->performAttack(attacker, this);
                attacker->setHighlighted(false);
                attacker->clearHighlightedPath();
                attacker->clearHighlightedAttackables();
                game_->clearHighlight();
                game_->setCurrentHighlightedAgent(nullptr);
                return;
            }
        }

        setZValue(20);
        // Always toggle agent highlight, regardless of position
        game_->toggleAgentHighlight(this);
        setHighlighted(!isHighlighted_);
        if (isHighlighted_) {
            // If highlighted, show movement and attack ranges
            qreal minDistance;
            Hexagon* nearestCell = game_->findNearestCell(pos() + boundingRect().center(), minDistance);
            if (nearestCell && minDistance < 100) {
                auto [path, attackableEnemies] = game_->bfs(nearestCell, agent_->getAgentType(), agent_->getMobility(), agent_->getAttackRange());
                game_->highlightPath(path, attackableEnemies);
                highlightedPath_ = path;
                highlightedAttackables_ = attackableEnemies;
            }
        } else {
            // If unhighlighted, clear path and attackables
            highlightedPath_.clear();
            highlightedAttackables_.clear();
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

    if (nearestCell && minDistance < 100) {
        QString cellValue = nearestCell->getValue();
        if (player_ == '1' && cellValue == "s1") {
            isValidPlacement = true;
        } else if (player_ == '2' && cellValue == "s2") {
            isValidPlacement = true;
        } else if (isHighlighted_) {
            bool isValidCell = true;
            if (agent_->getAgentType() == AgentType::WaterWalking) {
                if (cellValue != "~" && cellValue != " " && cellValue != "s2") {
                    isValidCell = false;
                }
            } else if (agent_->getAgentType() == AgentType::Grounded) {
                if (cellValue != " " && cellValue != "s1") {
                    isValidCell = false;
                }
            } else if (agent_->getAgentType() == AgentType::Floating) {
                if (cellValue == "#") {
                    isValidCell = false;
                }
            } else if (agent_->getAgentType() == AgentType::Flying) {
                if (player_ == '1' && cellValue != " " && cellValue != "s1") {
                    isValidCell = false;
                } else if (player_ == '2' && cellValue != " " && cellValue != "s2") {
                    isValidCell = false;
                }
            }
            if (cellValue == "1" || cellValue == "2") {
                isValidCell = false;
            }
            isValidPlacement = (isValidCell && std::find(highlightedPath_.begin(), highlightedPath_.end(), nearestCell) != highlightedPath_.end());
        }

        if (isValidPlacement) {
            setPos(nearestCell->getCenter() - boundingRect().center());
            originalPos_ = nearestCell->getCenter();
            agent_->setPosition(nearestCell);
            game_->drawBoard();
            game_->clearHighlight();
            isHighlighted_ = false;
            highlightedPath_.clear();
            highlightedAttackables_.clear();
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
