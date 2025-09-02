#pragma once
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

// 前向声明Player类
class Player;

class Equipment {
private:
    int ATK; // 装备提供的攻击力加成
    int DEF; // 装备提供的防御力加成

public:
    // 构造函数
    Equipment(int atk = 0, int def = 0);

    // 获取穿上装备后的玩家攻击力
    int getPlayerATK(const Player& player) const;

    // 获取穿上装备后的玩家防御力
    int getPlayerDEF(const Player& player) const;

    // 设置装备属性
    void setATK(int atk);
    void setDEF(int def);

    // 获取装备属性
    int getATK() const;
    int getDEF() const;
};

#endif // EQUIPMENT_H