// ½©Ê¬ Zombie
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Monster.h"

class Zombie : public Monster {
public:
    Zombie();
    int dropMoney(int random_number) const;

private:
    static const int health_max = 20;
    static const int attack = 3;
};

#endif
