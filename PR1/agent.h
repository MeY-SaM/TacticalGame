#ifndef AGENT_H
#define AGENT_H

#include <QDebug>
#include <QString>

class HexGame;
class Hexagon;

enum class AgentType {
    WaterWalking,
    Grounded,
    Flying,
    Floating
};

class Agent {
public:
    Agent(const QString& name, int hp, int mobility, int damage, int attackRange);
    virtual ~Agent() = default;

    virtual void attack(const std::string& target) const {
        qDebug() << Name << " attacks " << QString::fromStdString(target) << " with " << Damage << " damage!";
    }

    virtual void move(HexGame* game) = 0;
    virtual AgentType getAgentType() const = 0;

    QString getName() const { return Name; }
    int getHP() const { return Hp; }
    int getMobility() const { return Mobility; }
    int getDamage() const { return Damage; }
    int getAttackRange() const { return AttackRange; }

    void setHP(int hp) { Hp = hp; }
    void setPosition(Hexagon* hexagon) { hexagon_ = hexagon; }
    Hexagon* getPosition() const { return hexagon_; }

protected:
    QString Name;
    int Hp;
    int Mobility;
    int Damage;
    int AttackRange;
    Hexagon* hexagon_;
};

class WaterWalking : public Agent {
public:
    WaterWalking(const QString& name, int hp, int mobility, int damage, int attackRange);
    void move(HexGame* game) override;
    AgentType getAgentType() const override { return AgentType::WaterWalking; }
};

class Grounded : public Agent {
public:
    Grounded(const QString& name, int hp, int mobility, int damage, int attackRange);
    void move(HexGame* game) override;
    AgentType getAgentType() const override { return AgentType::Grounded; }
};

class Flying : public Agent {
public:
    Flying(const QString& name, int hp, int mobility, int damage, int attackRange);
    void move(HexGame* game) override;
    AgentType getAgentType() const override { return AgentType::Flying; }
};

class Floating : public Agent {
public:
    Floating(const QString& name, int hp, int mobility, int damage, int attackRange);
    void move(HexGame* game) override;
    AgentType getAgentType() const override { return AgentType::Floating; }
};

#endif // AGENT_H
