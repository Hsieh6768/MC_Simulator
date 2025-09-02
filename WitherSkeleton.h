// µòÁã÷¼÷Ã Wither Skeleton
#ifndef WITHERSKELETON_H
#define WITHERSKELETON_H
#include "Monster.h"

class WitherSkeleton : public Monster {
public:
    WitherSkeleton();
    int dropMoney(int random_number);

private:
    static const int health_max = 40;
    static const int attack = 7;
};

#endif
