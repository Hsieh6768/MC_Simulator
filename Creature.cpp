#include "Creature.h"

Creature::Creature(
    std::string name,
    int health_max,
    int health_cur,
    int attack
) : name(name),
health_max(health_max),
health_cur(health_cur),
attack(attack) {}

Creature::~Creature() {}

std::string Creature::getName() const {
    return this->name;
}

void Creature::setName(std::string name) {
    this->name = name;
}

int Creature::getHealthMax() const {
    return this->health_max;
}

void Creature::setHealthMax(int health_max) {
    this->health_max = health_max;
}

int Creature::getHealthCur() const {
    return this->health_cur;
}

void Creature::setHealthCur(int health_cur) {
    this->health_cur = health_cur;
}

int Creature::getAttack() const {
    return this->attack;
}

void Creature::setAttack(int attack) {
    this->attack = attack;
}
