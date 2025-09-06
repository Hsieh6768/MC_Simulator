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
    static const int health_max = 45;
    static const int attack = 9;
};

#endif
