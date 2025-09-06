// µòÁã÷¼÷Ã Wither Skeleton
#ifndef WITHER_SKELETON_H
#define WITHER_SKELETON_H
#include "Monster.h"

class WitherSkeleton : public Monster {
public:
    WitherSkeleton();
    int dropMoney(int random_number) const;

private:
    static const int health_max = 40;
    static const int attack = 7;
};

#endif
