#include "Skill.h"
#include <iostream>

// Skill 基类实现
Skill::Skill(const std::string& name, int cost, int round, int effect)
    : name(name), cost(cost), round(round), effect(effect) {}

void Skill::applyRoundEffect(Player& player) {
    // 基类默认不执行任何每回合效果
}

void Skill::endEffect(Player& player) {
    // 基类默认不执行任何结束效果
}

std::string Skill::getName() const {
    return name;
}

int Skill::getCost() const {
    return cost;
}

int Skill::getRound() const {
    return round;
}

int Skill::getEffect() const {
    return effect;
}

void Skill::decreaseRound() {
    if (round > 0) {
        round--;
    }
}

bool Skill::isActive() const {
    return round > 0;
}

// PowerSkill 实现
PowerSkill::PowerSkill()
    : Skill("力量强化", 10, 3, 3) {}

void PowerSkill::use(Player& player) {
    std::cout << name << "技能发动！攻击力增加" << effect << "点，持续" << round << "回合\n";
    player.setATK(player.getATK() + effect);
}

void PowerSkill::endEffect(Player& player) {
    std::cout << name << "效果结束，攻击力恢复\n";
    player.setATK(player.getATK() - effect);
}

// DefendSkill 实现
DefendSkill::DefendSkill()
    : Skill("防御姿态", 15, 1, 0) {}

void DefendSkill::use(Player& player) {
    std::cout << name << "技能发动！防御力翻倍\n";
    player.setDEF(player.getDEF() * 2);
}

void DefendSkill::endEffect(Player& player) {
    std::cout << name << "效果结束，防御力恢复\n";
    player.setDEF(player.getDEF() / 2);
}

// HealingSkill 实现
HealingSkill::HealingSkill()
    : Skill("生命恢复", 8, 3, 3) {}

void HealingSkill::use(Player& player) {
    std::cout << name << "技能发动！每回合回复" << effect << "点HP，持续" << round << "回合\n";
}

void HealingSkill::applyRoundEffect(Player& player) {
    if (isActive()) {
        int currentHP = player.getHP();
        player.setHP(currentHP + effect);
        std::cout << name << "效果生效，回复" << effect << "点HP\n";
        decreaseRound();
    }
}