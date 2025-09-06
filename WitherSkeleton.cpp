#include "WitherSkeleton.h"

WitherSkeleton::WitherSkeleton() : Monster("凋零骷髅", health_max, health_max, attack, "普通", true) {}

void WitherSkeleton::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：" << "凋零诅咒" << std::endl;
}

bool WitherSkeleton::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::WITHER_SKELETON_N == 1;
}

int WitherSkeleton::dropMoney(int random_number) const {
    return DropConstants::WITHER_SKELETON_BASE_DROP + random_number % DropConstants::WITHER_SKELETON_DROP_RANGE;
}
