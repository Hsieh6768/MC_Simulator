#include "WitherSkeleton.h"

WitherSkeleton::WitherSkeleton() : Monster("凋零骷髅", health_max, health_max, attack, "普通", true, { "凋零诅咒" }) {}

void WitherSkeleton::showInfo() const {
    std::cout << "生命值：" << getHealthCur()
        << "\t攻击力：" << attack
        << "\n级别：" << getType()
        << "\t特殊能力：1、" << getAbility(0) << std::endl;
}

bool WitherSkeleton::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    return random_number % SpecialAbilityConstants::WITHER_SKELETON_N == 1;
}

int WitherSkeleton::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::WITHER_SKELETON_BASE_DROP + random_number % DropConstants::WITHER_SKELETON_DROP_RANGE;
}
