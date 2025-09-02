#include "Equipment.h"
#include "Player.h" // 需要包含Player类的定义

// 构造函数
Equipment::Equipment(int atk, int def) : ATK(atk), DEF(def) {}

// 获取穿上装备后的玩家攻击力
int Equipment::getPlayerATK(const Player& player) const {
    // 假设Player类有getBaseATK()方法获取基础攻击力
    return player.getBaseATK() + ATK;
}

// 获取穿上装备后的玩家防御力
int Equipment::getPlayerDEF(const Player& player) const {
    // 假设Player类有getBaseDEF()方法获取基础防御力
    return player.getBaseDEF() + DEF;
}

// 设置装备属性
void Equipment::setATK(int atk) {
    ATK = atk;
}

void Equipment::setDEF(int def) {
    DEF = def;
}

// 获取装备属性
int Equipment::getATK() const {
    return ATK;
}

int Equipment::getDEF() const {
    return DEF;
}