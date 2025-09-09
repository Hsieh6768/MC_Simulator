// 终界龙 Ender Dragon
#ifndef ENDER_DRAGON_H
#define ENDER_DRAGON_H
#include "Monster.h"

class EnderDragon : public Monster {
public:
    EnderDragon();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int selectAbility(int random_number) const;  // 本回合触发特殊能力时选择应触发哪个特殊能力
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::ENDER_DRAGON_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::ENDER_DRAGON_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
