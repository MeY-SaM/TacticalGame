#include "agent.h"
#include "hexgame.h"
#include "draggableagent.h"
#include <random>
#include <QMessageBox>

Agent::Agent(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Name(name), Hp(hp), Mobility(mobility), Damage(damage), AttackRange(attackRange), hexagon_(nullptr) {}

void Agent::attack(DraggableAgent* defender, HexGame* game) {
    if (!defender || !game) {
        qDebug() << "Invalid defender or game in attack!";
        return;
    }

    int damage = Damage;
    defender->getAgent()->setHP(defender->getAgent()->getHP() - damage);
    qDebug() << Name << " attacks " << defender->getAgent()->getName() << " for " << damage << " damage.";

    bool defenderDied = (defender->getAgent()->getHP() <= 0);
    DraggableAgent* defenderToDelete = nullptr;
    if (defenderDied) {
        qDebug() << defender->getAgent()->getName() << " is defeated!";
        game->getScene()->removeItem(defender);
        if (defender->getPlayer() == '1') {
            game->getLeftHexagons().erase(
                std::remove(game->getLeftHexagons().begin(), game->getLeftHexagons().end(), defender),
                game->getLeftHexagons().end());
        } else {
            game->getRightHexagons().erase(
                std::remove(game->getRightHexagons().begin(), game->getRightHexagons().end(), defender),
                game->getRightHexagons().end());
        }
        defenderToDelete = defender;
        defender = nullptr;
    }

    DraggableAgent* attacker = nullptr;
    for (auto* da : game->getLeftHexagons()) {
        if (da->getAgent() == this) {
            attacker = da;
            break;
        }
    }
    if (!attacker) {
        for (auto* da : game->getRightHexagons()) {
            if (da->getAgent() == this) {
                attacker = da;
                break;
            }
        }
    }

    bool attackerDied = false;
    DraggableAgent* attackerToDelete = nullptr;
    if (defender) {
        int counterDamage = defender->getAgent()->getDamage() / 2;
        setHP(Hp - counterDamage);
        qDebug() << defender->getAgent()->getName() << " counters " << Name << " for " << counterDamage << " damage.";

        if (Hp <= 0) {
            qDebug() << Name << " is defeated!";
            if (attacker) {
                game->getScene()->removeItem(attacker);
                if (attacker->getPlayer() == '1') {
                    game->getLeftHexagons().erase(
                        std::remove(game->getLeftHexagons().begin(), game->getLeftHexagons().end(), attacker),
                        game->getLeftHexagons().end());
                } else {
                    game->getRightHexagons().erase(
                        std::remove(game->getRightHexagons().begin(), game->getRightHexagons().end(), attacker),
                        game->getRightHexagons().end());
                }
                attackerToDelete = attacker;
            }
            attackerDied = true;
        }
    }

    if (defender && !attackerDied) {
        Hexagon* defPos = defender->getAgent()->getPosition();
        std::vector<Hexagon*> freeNeighbors;
        for (int i = 0; i < 6; ++i) {
            Hexagon* neigh = defPos->getNeighbor(i);
            if (neigh) {
                QString val = neigh->getValue();
                bool valid = true;
                AgentType type = getAgentType();

                if (type == AgentType::WaterWalking) {
                    if (val == "#") valid = false;
                } else if (type == AgentType::Grounded) {
                    if (val == "~" || val == "#") valid = false;
                } else if (type == AgentType::Floating) {
                    if (val == "#") valid = false;
                } else if (type == AgentType::Flying) {
                }

                bool occupied = false;
                for (auto* da : game->getLeftHexagons()) {
                    if (da->getAgent()->getPosition() == neigh) occupied = true;
                }
                for (auto* da : game->getRightHexagons()) {
                    if (da->getAgent()->getPosition() == neigh) occupied = true;
                }

                if (valid && !occupied) freeNeighbors.push_back(neigh);
            }
        }

        if (!freeNeighbors.empty()) {
            std::vector<Hexagon*> validNeighbors;
            AgentType type = getAgentType();

            for (Hexagon* neigh : freeNeighbors) {
                QString val = neigh->getValue();
                bool valid = true;

                if (type == AgentType::WaterWalking) {
                    if (val == "#") valid = false;
                } else if (type == AgentType::Grounded) {
                    if (val == "~" || val == "#") valid = false;
                } else if (type == AgentType::Floating) {

                } else if (type == AgentType::Flying) {
                    if (val == "#" || val == "~") valid = false;
                }

                if (valid) {
                    validNeighbors.push_back(neigh);
                }
            }

            if (!validNeighbors.empty()) {
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_int_distribution<> dis(0, validNeighbors.size() - 1);
                int randIndex = dis(gen);
                Hexagon* newPos = validNeighbors[randIndex];

                if (attacker) {
                    attacker->setPos(newPos->getCenter() - attacker->boundingRect().center());
                    attacker->setOriginalPos(newPos->getCenter());
                    attacker->getAgent()->setPosition(newPos);
                    qDebug() << Name << " moved to a random valid neighbor of " << defender->getAgent()->getName();
                }
            } else {
                qDebug() << "No valid free neighbors for " << Name << " to move to.";
            }
        } else {
            qDebug() << "No valid free neighbors for " << Name << " to move to.";
        }
    }

    if (game->countAgentsOnBoard('1') == 0) {
        qDebug() << "Player 2 wins!";
        QMessageBox::information(game, "Game Over", "Player 2 wins! All Player 1 agents on board are defeated.");
        game->close();
    } else if (game->countAgentsOnBoard('2') == 0) {
        qDebug() << "Player 1 wins!";
        QMessageBox::information(game, "Game Over", "Player 1 wins! All Player 2 agents on board are defeated.");
        game->close();
    }

    game->clearHighlight();
    game->setCurrentHighlightedAgent(nullptr);
    game->drawBoard();

    if (defenderToDelete) {
        delete defenderToDelete;
    }
    if (attackerToDelete) {
        delete attackerToDelete;
    }
}

WaterWalking::WaterWalking(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void WaterWalking::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for WaterWalking move!";
        return;
    }

    DraggableAgent* draggable = nullptr;
    for (auto* da : game->getLeftHexagons()) {
        if (da->getAgent() == this) {
            draggable = da;
            break;
        }
    }
    if (!draggable) {
        for (auto* da : game->getRightHexagons()) {
            if (da->getAgent() == this) {
                draggable = da;
                break;
            }
        }
    }

    if (!draggable) {
        qDebug() << "No DraggableAgent found for WaterWalking!";
        return;
    }

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::WaterWalking, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for WaterWalking!";
        return;
    }

    draggable->clearHighlightedPath();
    draggable->clearHighlightedAttackables();
    draggable->setHighlightedPath(possibleMoves);
    draggable->setHighlightedAttackables(attackableEnemies);
    game->highlightPath(possibleMoves, attackableEnemies);
    qDebug() << "WaterWalking" << Name << " possible moves and attackable enemies highlighted.";
}

Grounded::Grounded(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void Grounded::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for Grounded move!";
        return;
    }

    DraggableAgent* draggable = nullptr;
    for (auto* da : game->getLeftHexagons()) {
        if (da->getAgent() == this) {
            draggable = da;
            break;
        }
    }
    if (!draggable) {
        for (auto* da : game->getRightHexagons()) {
            if (da->getAgent() == this) {
                draggable = da;
                break;
            }
        }
    }

    if (!draggable) {
        qDebug() << "No DraggableAgent found for Grounded!";
        return;
    }

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::Grounded, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Grounded!";
        return;
    }

    draggable->clearHighlightedPath();
    draggable->clearHighlightedAttackables();
    draggable->setHighlightedPath(possibleMoves);
    draggable->setHighlightedAttackables(attackableEnemies);
    game->highlightPath(possibleMoves, attackableEnemies);
    qDebug() << "Grounded" << Name << " possible moves and attackable enemies highlighted.";
}

Flying::Flying(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void Flying::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for Flying move!";
        return;
    }

    DraggableAgent* draggable = nullptr;
    for (auto* da : game->getLeftHexagons()) {
        if (da->getAgent() == this) {
            draggable = da;
            break;
        }
    }
    if (!draggable) {
        for (auto* da : game->getRightHexagons()) {
            if (da->getAgent() == this) {
                draggable = da;
                break;
            }
        }
    }

    if (!draggable) {
        qDebug() << "No DraggableAgent found for Flying!";
        return;
    }

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::Flying, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Flying!";
        return;
    }

    draggable->clearHighlightedPath();
    draggable->clearHighlightedAttackables();
    draggable->setHighlightedPath(possibleMoves);
    draggable->setHighlightedAttackables(attackableEnemies);
    game->highlightPath(possibleMoves, attackableEnemies);
    qDebug() << "Flying" << Name << " possible moves and attackable enemies highlighted.";
}

Floating::Floating(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void Floating::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for Floating move!";
        return;
    }

    DraggableAgent* draggable = nullptr;
    for (auto* da : game->getLeftHexagons()) {
        if (da->getAgent() == this) {
            draggable = da;
            break;
        }
    }
    if (!draggable) {
        for (auto* da : game->getRightHexagons()) {
            if (da->getAgent() == this) {
                draggable = da;
                break;
            }
        }
    }

    if (!draggable) {
        qDebug() << "No DraggableAgent found for Floating!";
        return;
    }

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::Floating, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Floating!";
        return;
    }

    draggable->clearHighlightedPath();
    draggable->clearHighlightedAttackables();
    draggable->setHighlightedPath(possibleMoves);
    draggable->setHighlightedAttackables(attackableEnemies);
    game->highlightPath(possibleMoves, attackableEnemies);
    qDebug() << "Floating" << Name << " possible moves and attackable enemies highlighted.";
}
