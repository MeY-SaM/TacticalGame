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
            if (!game_->canTakeAction()) {
                qDebug() << "Player" << attacker->getPlayer() << "has already taken an action this turn!";
                return;
            }
            auto it = std::find(attacker->getHighlightedAttackables().begin(),
                                attacker->getHighlightedAttackables().end(), this);
            if (it != attacker->getHighlightedAttackables().end()) {
                qDebug() << "Initiating attack from" << attacker->getAgent()->getName()
                << "to" << this->getAgent()->getName();
                attacker->getAgent()->attack(this, game_);
                attacker->setHighlighted(false);
                attacker->clearHighlightedPath();
                attacker->clearHighlightedAttackables();
                game_->clearHighlight();
                game_->setCurrentHighlightedAgent(nullptr);
                game_->incrementActions();
                game_->switchTurn();
                return;
            } else {
                qDebug() << "Target" << this->getAgent()->getName() << "not in attackable list!";
                return;
            }
        }

        if (player_ != game_->getCurrentPlayer()) {
            qDebug() << "Not your turn, Player" << player_;
            return;
        }

        if (!game_->canTakeAction() && !isHighlighted_) {
            qDebug() << "Player" << player_ << "has already taken an action this turn!";
            return;
        }

        setZValue(20);
        qreal minDistance;
        Hexagon* nearestCell = game_->findNearestCell(pos() + boundingRect().center(), minDistance);
        if (nearestCell && minDistance < 100) {
            if (!isHighlighted_) {
                qDebug() << "Highlighting moves for" << agent_->getName();
                agent_->move(game_);
                setHighlighted(true);
                game_->setCurrentHighlightedAgent(this);
            } else {
                qDebug() << "Clearing highlight for" << agent_->getName();
                game_->clearHighlight();
                setHighlighted(false);
                clearHighlightedPath();
                clearHighlightedAttackables();
                game_->setCurrentHighlightedAgent(nullptr);
            }
        } else {
            qDebug() << "No valid cell found for highlighting!";
        }
    }
    QGraphicsPolygonItem::mousePressEvent(event);
}

void DraggableAgent::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (player_ != game_->getCurrentPlayer()) {
        qDebug() << "Not your turn, Player" << player_;
        return;
    }
    setZValue(20);
    setPos(event->scenePos() - event->buttonDownPos(Qt::LeftButton));
    game_->clearHighlight();
}

void DraggableAgent::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (player_ != game_->getCurrentPlayer()) {
        qDebug() << "Not your turn, Player" << player_;
        setPos(originalPos_ - boundingRect().center());
        setZValue(10);
        QGraphicsPolygonItem::mouseReleaseEvent(event);
        return;
    }

    if (!game_->canTakeAction()) {
        qDebug() << "Player" << player_ << "has already taken an action this turn!";
        setPos(originalPos_ - boundingRect().center());
        setZValue(10);
        QGraphicsPolygonItem::mouseReleaseEvent(event);
        return;
    }

    qreal minDistance;
    Hexagon* nearestCell = game_->findNearestCell(event->scenePos(), minDistance);
    bool isValidPlacement = false;

    if (nearestCell && minDistance < 160) {
        QString cellValue = nearestCell->getValue();
        bool isValidCell = true;

        // بررسی تعداد agent‌های روی برد
        int agentsOnBoard = game_->countAgentsOnBoard(player_);
        bool isInitialPlacement = (player_ == '1' && qAbs(originalPos_.x() - 75) < 1) ||
                                  (player_ == '2' && qAbs(originalPos_.x() - 1109) < 1);

        if (isInitialPlacement) {
            if ((player_ == '1' && cellValue == "s1") || (player_ == '2' && cellValue == "s2")) {
                if (agentsOnBoard < 5) {
                    isValidPlacement = true;
                } else {
                    qDebug() << "Cannot place" << agent_->getName() << ": Maximum 5 agents allowed on board for Player" << player_;
                }
            }
        } else {
            if (agent_->getAgentType() == AgentType::WaterWalking) {
                if (cellValue == "#") isValidCell = false;
            } else if (agent_->getAgentType() == AgentType::Grounded) {
                if (cellValue == "~" || cellValue == "#") isValidCell = false;
            } else if (agent_->getAgentType() == AgentType::Floating) {
            } else if (agent_->getAgentType() == AgentType::Flying) {
                if (cellValue == "#" || cellValue == "~") isValidCell = false;
            }

            if (cellValue == "1" || cellValue == "2") {
                isValidCell = false;
            }

            isValidPlacement = (isValidCell && std::find(highlightedPath_.begin(), highlightedPath_.end(), nearestCell) != highlightedPath_.end());
        }

        if (isValidPlacement) {
            qDebug() << "Moving" << agent_->getName() << "to cell at" << nearestCell->getCenter();
            setPos(nearestCell->getCenter() - boundingRect().center());
            setOriginalPos(nearestCell->getCenter());
            agent_->setPosition(nearestCell);
            game_->drawBoard();
            game_->clearHighlight();
            setHighlighted(false);
            clearHighlightedPath();
            clearHighlightedAttackables();
            game_->setCurrentHighlightedAgent(nullptr);
            game_->incrementActions();
            game_->switchTurn();
        } else {
            qDebug() << "Invalid move for" << agent_->getName() << "to cell" << cellValue;
            setPos(originalPos_ - boundingRect().center());
        }
    } else {
        qDebug() << "No valid cell found for" << agent_->getName();
        setPos(originalPos_ - boundingRect().center());
    }
    setZValue(10);
    QGraphicsPolygonItem::mouseReleaseEvent(event);
}
