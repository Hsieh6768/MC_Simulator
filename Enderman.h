// ÷’ΩÁ π’ﬂ Enderman
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
    static const int health_max = MonsterBaseAttributes::ENDERMAN_MAX_HEALTH;
    static const int attack = MonsterBaseAttributes::ENDERMAN_ATTACK;
};

#endif
