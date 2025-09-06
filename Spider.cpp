#include "Spider.h"

Spider::Spider() : Monster("蜘蛛", health_max, health_max, attack, "普通", false) {}

void Spider::showInfo() const {
    std::cout << "生命值：" << health_cur
              << "\t攻击力：" << attack
              << "\n级别：" << type
              << "\t特殊能力：" << "无" << std::endl;
}

bool Spider::useSpecialAbility(int random_number) const {
    return false;
}

int Spider::dropMoney(int random_number) const {
    return DropConstants::SPIDER_BASE_DROP + random_number % DropConstants::SPIDER_DROP_RANGE;
}

