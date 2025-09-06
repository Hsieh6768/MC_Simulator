// ¡“—Ê π’ﬂ Blaze
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
    static const int health_max = MonsterBaseAttributes::BLAZE_MAX_HEALTH;
    static const int attack = MonsterBaseAttributes::BLAZE_ATTACK;
};

#endif
