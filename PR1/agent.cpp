#include "agent.h"
#include "hexgame.h"

Agent::Agent(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Name(name), Hp(hp), Mobility(mobility), Damage(damage), AttackRange(attackRange), hexagon_(nullptr) {}

WaterWalking::WaterWalking(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void WaterWalking::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for WaterWalking move!";
        return;
    }

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::WaterWalking, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for WaterWalking!";
        return;
    }

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

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::Grounded, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Grounded!";
        return;
    }

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

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::Flying, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Flying!";
        return;
    }

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

    auto [possibleMoves, attackableEnemies] = game->bfs(hexagon_, AgentType::Floating, Mobility, AttackRange);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Floating!";
        return;
    }

    game->highlightPath(possibleMoves, attackableEnemies);
    qDebug() << "Floating" << Name << " possible moves and attackable enemies highlighted.";
}
