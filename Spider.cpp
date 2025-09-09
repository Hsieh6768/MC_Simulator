#include "Spider.h"

Spider::Spider() : Monster("蜘蛛", health_max, health_max, attack, "普通", false, { "无" }) {}

void Spider::showInfo() const {
    std::cout << "生命值：" << getHealthCur()
        << "\t攻击力：" << attack
        << "\n级别：" << getType()
        << "\t特殊能力：" << getAbility(0) << std::endl;
}

bool Spider::useSpecialAbility(int random_number) const {
    return false;  // 无特殊能力
}

int Spider::dropMoney(int random_number) const {
    // 绿宝石掉落值=基础掉落值+范围波动值
    return DropConstants::SPIDER_BASE_DROP + random_number % DropConstants::SPIDER_DROP_RANGE;
}
