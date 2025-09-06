// ÷©÷Î Spider
#ifndef SPIDER_H
#define SPIDER_H
#include "Monster.h"

class Spider : public Monster {
public:
    Spider();

    void showInfo() const override;
    bool useSpecialAbility(int random_number) const override;
    int dropMoney(int random_number) const override;

private:
    static const int health_max = 24;
    static const int attack = 4;
};

#endif
