#include "Monster.h"

Monster::Monster(
    std::string name,
    int health_max,
    int health_cur,
    int attack,
    std::string type,
    bool has_special_ability,
    std::vector<std::string> special_ability, 
    std::vector<std::string> special_ability_description
) : Creature(name, health_max, health_cur, attack),
type(type),
has_special_ability(has_special_ability),
special_ability(special_ability), 
special_ability_description(special_ability_description) {}

std::string Monster::getType() const {
    return this->type;
}

bool Monster::hasSpecialAbility() const {
    return this->has_special_ability;
}

std::string Monster::getAbility(int index) const {
    return special_ability[index];
}

std::string Monster::getAbilityDescription(int index) const {
    return special_ability_description[index];
}
