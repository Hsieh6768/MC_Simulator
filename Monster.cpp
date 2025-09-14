#include "Monster.h"

Monster::Monster(
    std::string name,
    int health_max,
    int health_cur,
    int attack,
    std::string type,
    std::string description,
    MonsterBuff buff, 
    bool has_special_ability,
    std::vector<std::string> special_ability, 
    std::vector<std::string> special_ability_description
) : Creature(name, health_max, health_cur, attack),
type(type),
description(description),
buff(buff), 
has_special_ability(has_special_ability),
special_ability(special_ability), 
special_ability_description(special_ability_description) {}

std::string Monster::getType() const {
    return this->type;
}

std::string Monster::getDescription() const {
    return this->description;
}

MonsterBuff Monster::getMonsterBuff() const {
    return this->buff;
}

void Monster::setMonsterBuff(const MonsterBuff buff) {
    this->buff = buff;
}

void Monster::updateMonsterBuffs() {
    if (buff.duration == 0) {  // 增益持续时间结束
        buff.attack_bonus = 0;
        buff.activated = false;
    }
    if (buff.duration > 0) {
        buff.duration--;
    }
    buff.dodged = false;  // 重置闪避状态
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
