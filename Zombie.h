// ½©Ê¬ Zombie
#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "Monster.h"

class Zombie : public Monster {
public:
    Zombie();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = 20;
    static const int attack = 3;
};

#endif
