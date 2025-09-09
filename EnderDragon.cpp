#include "EnderDragon.h"

EnderDragon::EnderDragon() : Monster("终界龙", health_max, health_max, attack, "史诗", true, { "冲撞攻击", "龙息腐蚀" }) {}

void EnderDragon::showInfo() const {
    std::cout << "生命值：" << getHealthCur()
        << "\t攻击力：" << attack
        << "\n级别：" << getType()
        << "\t特殊能力：1、" << getAbility(0) << "；2、" << getAbility(1)
        << std::endl;
}

bool EnderDragon::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    return random_number % SpecialAbilityConstants::ENDER_DRAGON_N == 1;
}

int EnderDragon::selectAbility(int random_number) const {
    // 触发特殊能力时随机选择其一
    return random_number % 2;
}

int EnderDragon::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::ENDER_DRAGON_BASE_DROP + random_number % DropConstants::ENDER_DRAGON_DROP_RANGE;
}
