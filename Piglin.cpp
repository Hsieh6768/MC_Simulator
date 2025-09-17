#include "Piglin.h"

Piglin::Piglin() : Monster("猪灵", health_max, health_max, attack, "普通", 
    "下界的智慧住民，热爱黄金，会对没有金装备的玩家发动攻击。", { 0, 0, false, false }, false, {"无"}) {}

void Piglin::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << getAttack()
              << "\t级别: ";
    ColorManager::COLOR_PRINT(getType(), BLUE);
    std::cout << "\n特点: " << getDescription()
              << "\n特殊能力: " << getAbility(0) << std::endl;
}

std::string Piglin::getTypeName() const {
    return "Piglin";
}

bool Piglin::useSpecialAbility(int random_number) const {
    return false;  // 无特殊能力
}

int Piglin::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::PIGLIN_BASE_DROP + random_number % DropConstants::PIGLIN_DROP_RANGE;
}
