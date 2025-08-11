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

    std::vector<Hexagon*> possibleMoves = game->bfs(hexagon_, AgentType::WaterWalking, Mobility);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for WaterWalking!";
        return;
    }

    game->highlightPath(possibleMoves);
    qDebug() << "WaterWalking" << Name << " possible moves highlighted.";
}

Grounded::Grounded(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void Grounded::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for Grounded move!";
        return;
    }

    std::vector<Hexagon*> possibleMoves = game->bfs(hexagon_, AgentType::Grounded, Mobility);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Grounded!";
        return;
    }

    game->highlightPath(possibleMoves);
    qDebug() << "Grounded" << Name << " possible moves highlighted.";
}

Flying::Flying(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void Flying::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for Flying move!";
        return;
    }

    std::vector<Hexagon*> possibleMoves = game->bfs(hexagon_, AgentType::Flying, Mobility);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Flying!";
        return;
    }

    game->highlightPath(possibleMoves);
    qDebug() << "Flying" << Name << " possible moves highlighted.";
}

Floating::Floating(const QString& name, int hp, int mobility, int damage, int attackRange)
    : Agent(name, hp, mobility, damage, attackRange) {}

void Floating::move(HexGame* game) {
    if (!game || !hexagon_) {
        qDebug() << "Invalid game or hexagon position for Floating move!";
        return;
    }

    std::vector<Hexagon*> possibleMoves = game->bfs(hexagon_, AgentType::Floating, Mobility);
    if (possibleMoves.empty()) {
        qDebug() << "No valid moves available for Floating!";
        return;
    }

    game->highlightPath(possibleMoves);
    qDebug() << "Floating" << Name << " possible moves highlighted.";
}
