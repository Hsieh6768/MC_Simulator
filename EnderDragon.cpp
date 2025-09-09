#include "EnderDragon.h"

EnderDragon::EnderDragon() : Monster("�ս���", health_max, health_max, attack, "ʷʫ", true, { "��ײ����", "��Ϣ��ʴ" }) {}

void EnderDragon::showInfo() const {
    std::cout << "����ֵ��" << getHealthCur()
        << "\t��������" << attack
        << "\n����" << getType()
        << "\t����������1��" << getAbility(0) << "��2��" << getAbility(1)
        << std::endl;
}

bool EnderDragon::useSpecialAbility(int random_number) const {
    // ����Ϊ1ʱ�ڱ��غ�ʹ����������
    return random_number % SpecialAbilityConstants::ENDER_DRAGON_N == 1;
}

int EnderDragon::selectAbility(int random_number) const {
    // ������������ʱ���ѡ����һ
    return random_number % 2;
}

int EnderDragon::dropMoney(int random_number) const {
    // �̱�ʯ����ֵ=��������ֵ+��Χ����ֵ
    return DropConstants::ENDER_DRAGON_BASE_DROP + random_number % DropConstants::ENDER_DRAGON_DROP_RANGE;
}
