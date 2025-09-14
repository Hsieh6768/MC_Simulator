#ifndef SKILL_H
#define SKILL_H

#include "ColorManager.h"
#include <string>
#include <memory>
#include <algorithm>

// 前向声明
class Player;
class Monster;

class Skill {
protected:
    std::string name;
    std::string description;
    int cost;           // 魔法消耗
    int cooldown;       // 冷却回合
    int currentCooldown;// 当前冷却

public:
    Skill(const std::string& name = "", const std::string& desc = "",
        int cost = 0, int cooldown = 0);
    virtual ~Skill() = default;

    // 使用技能（纯虚函数）
    virtual bool use(Player& caster, Monster& target) = 0;

    // 冷却处理
    void reduceCooldown();
    void resetCooldown();

    // 获取信息
    std::string getName() const;
    std::string getDescription() const;
    int getCost() const;
    int getCooldown() const;
    int getCurrentCooldown() const;
    bool isReady() const;

    // 显示技能信息
    virtual void displayInfo() const;
};

// 攻击技能
class AttackSkill : public Skill {
private:
    int damage;  // 瞬时伤害

public:
    AttackSkill(const std::string& name, const std::string& desc,
        int cost, int cooldown, int damage);

    bool use(Player& caster, Monster& target) override;
    void displayInfo() const override;
};

// 治疗技能
class HealSkill : public Skill {
private:
    int healAmount;  // 回复生命值

public:
    HealSkill(const std::string& name, const std::string& desc,
        int cost, int cooldown, int healAmount);

    bool use(Player& caster, Monster& target) override;
    void displayInfo() const override;
};

// 增益技能
class BuffSkill : public Skill {
private:
    int duration;
    int attackBonus;
    int defenseBonus;

public:
    BuffSkill(const std::string& name, const std::string& desc,
        int cost, int cooldown, int duration, int atkBonus, int defBonus);

    bool use(Player& caster, Monster& target) override;
    void displayInfo() const override;
};

// 技能管理器
class SkillManager {
public:
    static std::unique_ptr<Skill> createSkill(const std::string& skillType);
};

#endif // SKILL_H