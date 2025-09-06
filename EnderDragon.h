// ÷’ΩÁ¡˙ Ender Dragon
#ifndef ENDER_DRAGON_H
#define ENDER_DRAGON_H
#include "Monster.h"

class EnderDragon : public Monster {
public:
    EnderDragon();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = MonsterBaseAttributes::ENDER_DRAGON_MAX_HEALTH;
    static const int attack = MonsterBaseAttributes::ENDER_DRAGON_ATTACK;
};

#endif
