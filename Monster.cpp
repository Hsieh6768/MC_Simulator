#include "Monster.h"

Monster::Monster(
    std::string name, 
    int health_max, 
    int health_cur, 
    int attack, 
    std::string type, 
    bool has_special_ability
) : Creature(name, health_max, health_cur, attack), 
    type(type), 
    has_special_ability(has_special_ability) {}

Monster::~Monster() {}

bool Monster::hasSpecialAbility() const {
    return this->has_special_ability;
}
