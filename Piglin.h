// ���� Piglin
#ifndef PIGLIN_H
#define PIGLIN_H
#include "Monster.h"

class Piglin : public Monster {
public:
    Piglin();
    int dropMoney(int random_number);

private:
    static const int health_max = 20;
    static const int attack = 4;
};

#endif
