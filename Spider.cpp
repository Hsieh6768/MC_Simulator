#include "Spider.h"

Spider::Spider() : Monster("蜘蛛", health_max, health_max, attack, "普通") {}

int Spider::dropMoney(int random_number) const override {
    return DropConstants::SPIDER_BASE_DROP + random_number % DropConstants::SPIDER_DROP_RANGE;
}

