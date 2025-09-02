#include "Skill.h"
#include <iostream>

// Skill ����ʵ��
Skill::Skill(const std::string& name, int cost, int round, int effect)
    : name(name), cost(cost), round(round), effect(effect) {}

void Skill::applyRoundEffect(Player& player) {
    // ����Ĭ�ϲ�ִ���κ�ÿ�غ�Ч��
}

void Skill::endEffect(Player& player) {
    // ����Ĭ�ϲ�ִ���κν���Ч��
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

// PowerSkill ʵ��
PowerSkill::PowerSkill()
    : Skill("����ǿ��", 10, 3, 3) {}

void PowerSkill::use(Player& player) {
    std::cout << name << "���ܷ���������������" << effect << "�㣬����" << round << "�غ�\n";
    player.setATK(player.getATK() + effect);
}

void PowerSkill::endEffect(Player& player) {
    std::cout << name << "Ч���������������ָ�\n";
    player.setATK(player.getATK() - effect);
}

// DefendSkill ʵ��
DefendSkill::DefendSkill()
    : Skill("������̬", 15, 1, 0) {}

void DefendSkill::use(Player& player) {
    std::cout << name << "���ܷ���������������\n";
    player.setDEF(player.getDEF() * 2);
}

void DefendSkill::endEffect(Player& player) {
    std::cout << name << "Ч���������������ָ�\n";
    player.setDEF(player.getDEF() / 2);
}

// HealingSkill ʵ��
HealingSkill::HealingSkill()
    : Skill("�����ָ�", 8, 3, 3) {}

void HealingSkill::use(Player& player) {
    std::cout << name << "���ܷ�����ÿ�غϻظ�" << effect << "��HP������" << round << "�غ�\n";
}

void HealingSkill::applyRoundEffect(Player& player) {
    if (isActive()) {
        int currentHP = player.getHP();
        player.setHP(currentHP + effect);
        std::cout << name << "Ч����Ч���ظ�" << effect << "��HP\n";
        decreaseRound();
    }
}