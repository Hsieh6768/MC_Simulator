#include "EnderDragon.h"

EnderDragon::EnderDragon() : Monster("�ս���", health_max, health_max, attack, "ʷʫ", true) {}

void EnderDragon::showInfo() const {
    std::cout << "����ֵ��" << health_cur
              << "\t��������" << attack
              << "\n����" << type
              << "\t����������" << "��ײ��������Ϣ��ʴ" << std::endl;
}

bool EnderDragon::useSpecialAbility(int random_number) const {
    return random_number % SpecialAbilityConstants::ENDER_DRAGON_N == 1;
}

int EnderDragon::dropMoney(int random_number) const {
    return DropConstants::ENDER_DRAGON_BASE_DROP + random_number % DropConstants::ENDER_DRAGON_DROP_RANGE;
}
