// 僵尸 Zombie
#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Monster.h"

class Zombie : public Monster {
public:
    Zombie();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::ZOMBIE_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::ZOMBIE_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
