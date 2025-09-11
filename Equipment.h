#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>
#include <iostream>

class Equipment {
public:

    // 构造函数
    Equipment(std::string name = "无装备", int atk = 0, int def = 0,
        int value = 0, std::string type = "无");

    // 显示装备信息
    virtual void displayInfo() const;

    // 获取装备名称
    std::string getName() const;

    // 获取装备攻击力加成
    int getAttack() const;

    // 获取装备防御力加成
    int getDefense() const;

    // 获取装备价值
    int getValue() const;

    // 获取装备类型
    std::string getType() const;

    // 比较装备（用于排序）
    bool operator<(const Equipment& other) const;

    // 虚析构函数
    virtual ~Equipment() = default;

private:
    std::string name;
    int attack;
    int defense;
    int value;  // 装备价值
    std::string type; // 装备类型：weapon, armor
};

// 武器类
class Weapon : public Equipment {
public:
    Weapon(std::string name = "无武器", int atk = 0, int value = 0);
    void displayInfo() const override;
};

// 护甲类
class Armor : public Equipment {
public:
    Armor(std::string name = "无护甲", int def = 0, int value = 0);
    void displayInfo() const override;
};

// 预定义装备类型
namespace EquipmentTypes {
    // 武器
    extern const Weapon WOODEN_SWORD;
    extern const Weapon IRON_SWORD;
    extern const Weapon DIAMOND_SWORD;

    // 防具
    extern const Armor LEATHER_ARMOR;
    extern const Armor IRON_ARMOR;
    extern const Armor DIAMOND_ARMOR;
}

#endif // EQUIPMENT_H