// ÷©÷Î Spider
#ifndef SPIDER_H
#define SPIDER_H
#include "Monster.h"

class Spider : public Monster {
public:
    Spider();
    int dropMoney(int random_number);

private:
    static const int health_max = 24;
    static const int attack = 4;
};

#endif
