#include "Spider.h"

Spider::Spider() : Monster("蜘蛛", health_max, health_max, attack, "普通", 
    "夜间出没的敏捷生物，能爬墙并在黑暗中追逐玩家。", { 0, 0, false, false }, false, {"无"}) {}

void Spider::showInfo() const {
    std::cout << "生命值: " << getHealthCur()
              << "\t攻击力: " << getAttack()
              << "\t级别: ";
    ColorManager::COLOR_PRINT(getType(), BLUE);
    std::cout << "\n特点: " << getDescription()
              << "\n特殊能力: " << getAbility(0) << std::endl;
}

std::string Spider::getTypeName() const {
    return "Spider";
}

bool Spider::useSpecialAbility(int random_number) const {
    return false;  // 无特殊能力
}

int Spider::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::SPIDER_BASE_DROP + random_number % DropConstants::SPIDER_DROP_RANGE;
}
