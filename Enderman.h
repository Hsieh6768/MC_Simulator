// 终界使者 Enderman
#ifndef ENDERMAN_H
#define ENDERMAN_H

#include "Monster.h"

class Enderman : public Monster {
public:
    Enderman();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::ENDERMAN_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::ENDERMAN_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
