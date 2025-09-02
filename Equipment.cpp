#include "Equipment.h"
#include "Player.h" // ��Ҫ����Player��Ķ���

// ���캯��
Equipment::Equipment(int atk, int def) : ATK(atk), DEF(def) {}

// ��ȡ����װ�������ҹ�����
int Equipment::getPlayerATK(const Player& player) const {
    // ����Player����getBaseATK()������ȡ����������
    return player.getBaseATK() + ATK;
}

// ��ȡ����װ�������ҷ�����
int Equipment::getPlayerDEF(const Player& player) const {
    // ����Player����getBaseDEF()������ȡ����������
    return player.getBaseDEF() + DEF;
}

// ����װ������
void Equipment::setATK(int atk) {
    ATK = atk;
}

void Equipment::setDEF(int def) {
    DEF = def;
}

// ��ȡװ������
int Equipment::getATK() const {
    return ATK;
}

int Equipment::getDEF() const {
    return DEF;
}