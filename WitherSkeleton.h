// 凋零骷髅 Wither Skeleton
#ifndef WITHER_SKELETON_H
#define WITHER_SKELETON_H
#include "Monster.h"

class WitherSkeleton : public Monster {
public:
    WitherSkeleton();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::WITHER_SKELETON_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::WITHER_SKELETON_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
