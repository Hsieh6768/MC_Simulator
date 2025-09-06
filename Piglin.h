// ÷Ì¡È Piglin
#ifndef PIGLIN_H
#define PIGLIN_H
#include "Monster.h"

class Piglin : public Monster {
public:
    Piglin();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = 20;
    static const int attack = 4;
};

#endif
