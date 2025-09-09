#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

class Equipment {
public:
    std::string name;
    int attack;
    int defense;
    int value;  // 装备价值
    std::string type; // 装备类型：weapon, armor, accessory

    // 构造函数
    Equipment(std::string name = "无装备", int atk = 0, int def = 0,
        int value = 0, std::string type = "weapon");

    // 显示装备信息
    void displayInfo() const;

    // 获取装备价值
    int getValue() const;

    // 装备升级
    void upgrade(int atkBonus = 0, int defBonus = 0);

    // 获取装备类型
    std::string getType() const;

    // 比较装备（用于排序）
    bool operator<(const Equipment& other) const;
};

// 预定义装备类型
namespace EquipmentTypes {
    // 武器
    extern const Equipment WOODEN_SWORD;
    extern const Equipment STONE_SWORD;
    extern const Equipment IRON_SWORD;
    extern const Equipment DIAMOND_SWORD;
    extern const Equipment FIRE_SWORD;
    extern const Equipment ICE_SWORD;

    // 防具
    extern const Equipment LEATHER_ARMOR;
    extern const Equipment IRON_ARMOR;
    extern const Equipment DIAMOND_ARMOR;
    extern const Equipment FIRE_ARMOR;
    extern const Equipment ICE_ARMOR;

    // 饰品
    extern const Equipment HEALTH_RING;
    extern const Equipment MANA_RING;
    extern const Equipment LUCKY_CHARM;
}

#endif // EQUIPMENT_H