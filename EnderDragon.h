// Д©У°Бъ Ender Dragon
#ifndef ENDER_DRAGON_H
#define ENDER_DRAGON_H
#include "Monster.h"

class EnderDragon : public Monster {
public:
    EnderDragon();
    int dropMoney(int random_number) const;

private:
    static const int health_max = 150;
    static const int attack = 15;
};

#endif
