// 烈焰使者 Blaze
#ifndef BLAZE_H
#define BLAZE_H
#include "Monster.h"

class Blaze : public Monster {
public:
    Blaze();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::BLAZE_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::BLAZE_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
