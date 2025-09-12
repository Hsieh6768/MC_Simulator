#include "Blaze.h"

Blaze::Blaze() : Monster("烈焰使者", health_max, health_max, attack, "精英", true, { "火球攻击" }) {}

void Blaze::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << attack
              << "\n级别: " << getType()
              << "\t特殊能力: 1. " << getAbility(0) << std::endl;
}

bool Blaze::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    return random_number % SpecialAbilityConstants::BLAZE_N == 1;
}

int Blaze::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::BLAZE_BASE_DROP + random_number % DropConstants::BLAZE_DROP_RANGE;
}
