// 猪灵 Piglin
#ifndef PIGLIN_H
#define PIGLIN_H
#include "Monster.h"

class Piglin : public Monster {
public:
    Piglin();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::PIGLIN_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::PIGLIN_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
