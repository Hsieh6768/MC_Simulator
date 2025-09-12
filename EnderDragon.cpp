#include "EnderDragon.h"

EnderDragon::EnderDragon() : Monster("终界龙", health_max, health_max, attack, "史诗", true, 
    { "冲撞攻击", "龙息腐蚀" }, 
    { "本回合发动一次势不可挡的俯冲，对目标造成 18 点巨额伤害。", 
      "喷吐出一团浓郁的龙息，使目标在 3 回合内持续受到 3 点腐蚀伤害。"}) {}

void EnderDragon::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << attack
              << "\t级别: " << getType()
              << "\n特殊能力: 1. " << getAbility(0) 
              << "\t效果: " << getAbilityDescription(0)
              << "\n2. " << getAbility(1)
              << "\t效果: " << getAbilityDescription(1)
              << std::endl;
}

bool EnderDragon::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    if (random_number % SpecialAbilityConstants::ENDER_DRAGON_N == 1) {
        return true;
    }
    else {
        return false;
    }
}

int EnderDragon::selectAbility(int random_number) const {
    // 触发特殊能力时随机选择其一
    return random_number % 2;
}

int EnderDragon::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::ENDER_DRAGON_BASE_DROP + random_number % DropConstants::ENDER_DRAGON_DROP_RANGE;
}
