#include "Enderman.h"

Enderman::Enderman() : Monster("终界使者", health_max, health_max, attack, "精英", 
    "高大的黑色生物，能够瞬移并拾起方块，讨厌被注视。", { 0, 0, false, false }, true,
    { "瞬间移动" }, { "可闪避至战场上的任意位置，免疫下回合所有伤害。"}) {}

void Enderman::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << getAttack()
              << "\t级别: ";
    ColorManager::COLOR_PRINT(getType(), YELLOW);
    std::cout << "\n特点: " << getDescription()
              << "\n特殊能力: \n  1." << getAbility(0) 
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
