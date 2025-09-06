#include "Spider.h"

Spider::Spider() : Monster("֩��", health_max, health_max, attack, "��ͨ", false) {}

void Spider::showInfo() const {
    std::cout << "����ֵ��" << health_cur
              << "\t��������" << attack
              << "\n����" << type
              << "\t����������" << "��" << std::endl;
}

bool Spider::useSpecialAbility(int random_number) const {
    return false;
}

int Spider::dropMoney(int random_number) const {
    return DropConstants::SPIDER_BASE_DROP + random_number % DropConstants::SPIDER_DROP_RANGE;
}

