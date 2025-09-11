#include "Monster.h"

Monster::Monster(
    std::string name,
    int health_max,
    int health_cur,
    int attack,
    std::string type,
    bool has_special_ability,
    std::vector<std::string> special_ability
) : Creature(name, health_max, health_cur, attack),
type(type),
has_special_ability(has_special_ability),
special_ability(special_ability) {}

Monster::~Monster() {}

std::string Monster::getType() const {
    return this->type;
}

bool Monster::hasSpecialAbility() const {
    return this->has_special_ability;
}

std::string Monster::getAbility(int index) const {
    return special_ability[index];
}
