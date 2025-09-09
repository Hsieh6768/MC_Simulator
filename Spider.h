// 蜘蛛 Spider
#ifndef SPIDER_H
#define SPIDER_H
#include "Monster.h"

class Spider : public Monster {
public:
    Spider();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::SPIDER_MAX_HEALTH;  // 同种怪物固定最大生命值
    static const int attack = MonsterBaseAttributes::SPIDER_ATTACK;  // 同种怪物固定基础攻击力
};

#endif
