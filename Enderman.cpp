#include "Enderman.h"

Enderman::Enderman() : Monster("终界使者", health_max, health_max, attack, "精英", true, 
    { "瞬间移动" }, { "可闪避至战场上的任意位置，免疫下回合所有伤害。"}) {}

void Enderman::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << attack
              << "\t级别: " << getType()
              << "\n特殊能力: 1. " << getAbility(0) 
              << "\t效果: " << getAbilityDescription(0)
              << std::endl;
}

bool Enderman::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    return random_number % SpecialAbilityConstants::ENDERMAN_N == 1;
}

int Enderman::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::ENDERMAN_BASE_DROP + random_number % DropConstants::ENDERMAN_DROP_RANGE;
}
