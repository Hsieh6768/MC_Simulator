// Д©У°Бъ Ender Dragon
#ifndef ENDERDRAGON_H
#define ENDERDRAGON_H
#include "Monster.h"

class EnderDragon : public Monster {
public:
    EnderDragon();
    int dropMoney(int random_number);

private:
    static const int health_max = 150;
    static const int attack = 15;
};

#endif
