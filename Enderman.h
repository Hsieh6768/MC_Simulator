// ÷’ΩÁ π’ﬂ Enderman
#ifndef ENDERMAN_H
#define ENDERMAN_H
#include "Monster.h"

class Enderman : public Monster {
public:
    Enderman();
    int dropMoney(int random_number);

private:
    static const int health_max = 45;
    static const int attack = 9;
};

#endif
