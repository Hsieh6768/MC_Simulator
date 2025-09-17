#include "Blaze.h"

Blaze::Blaze() : Monster("烈焰使者", health_max, health_max, attack, "精英", 
    "来自下界的火焰生物，能在空中悬浮并发射致命的火球。", { 0, 0, false, false }, true,
    { "火球攻击" }, { "本回合凝聚烈焰，发射一枚火球，造成额外 4 点火焰伤害。"}) {}

void Blaze::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << getAttack()
              << "\t级别: ";
    ColorManager::COLOR_PRINT(getType(), YELLOW);
    std::cout << "\n特点: " << getDescription()
              << "\n特殊能力: \n  1." << getAbility(0) 
              << "\t效果: " << getAbilityDescription(0) 
              << std::endl;
}

std::string Blaze::getTypeName() const {
    return "Blaze";
}

bool Blaze::useSpecialAbility(int random_number) const {
    // 余数为1时在本回合使用特殊能力
    return random_number % SpecialAbilityConstants::BLAZE_N == 1;
}

int Blaze::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::BLAZE_BASE_DROP + random_number % DropConstants::BLAZE_DROP_RANGE;
}
