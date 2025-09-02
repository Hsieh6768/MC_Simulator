#pragma once
#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "Player.h"

class Skill {
protected:
    std::string name;    // 技能名称
    int cost;            // 技能消耗
    int round;           // 技能持续回合数
    int effect;          // 技能效果值

public:
    // 构造函数
    Skill(const std::string& name = "", int cost = 0, int round = 0, int effect = 0);
    virtual ~Skill() = default;

    // 纯虚函数：使用技能
    virtual void use(Player& player) = 0;

    // 虚函数：每回合效果（可选实现）
    virtual void applyRoundEffect(Player& player);

    // 虚函数：结束效果（可选实现）
    virtual void endEffect(Player& player);

    // 获取技能信息
    std::string getName() const;
    int getCost() const;
    int getRound() const;
    int getEffect() const;

    // 减少持续回合数
    void decreaseRound();

    // 检查技能是否还在持续
    bool isActive() const;
};

// 增加攻击力的技能
class PowerSkill : public Skill {
public:
    PowerSkill();
    void use(Player& player) override;
    void endEffect(Player& player) override;
};

// 增加防御力的技能
class DefendSkill : public Skill {
public:
    DefendSkill();
    void use(Player& player) override;
    void endEffect(Player& player) override;
};

// 回复生命的技能
class HealingSkill : public Skill {
public:
    HealingSkill();
    void use(Player& player) override;
    void applyRoundEffect(Player& player) override;
};

#endif // SKILL_H