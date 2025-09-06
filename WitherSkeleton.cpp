#include "WitherSkeleton.h"

WitherSkeleton::WitherSkeleton() : Monster("凋零骷髅", health_max, health_max, attack, "普通") {}

int WitherSkeleton::dropMoney(int random_number) const override {
    return DropConstants::WITHER_SKELETON_BASE_DROP + random_number % DropConstants::WITHER_SKELETON_DROP_RANGE;
}
