#pragma once
#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "Player.h"

class Skill {
protected:
    std::string name;    // ��������
    int cost;            // ��������
    int round;           // ���ܳ����غ���
    int effect;          // ����Ч��ֵ

public:
    // ���캯��
    Skill(const std::string& name = "", int cost = 0, int round = 0, int effect = 0);
    virtual ~Skill() = default;

    // ���麯����ʹ�ü���
    virtual void use(Player& player) = 0;

    // �麯����ÿ�غ�Ч������ѡʵ�֣�
    virtual void applyRoundEffect(Player& player);

    // �麯��������Ч������ѡʵ�֣�
    virtual void endEffect(Player& player);

    // ��ȡ������Ϣ
    std::string getName() const;
    int getCost() const;
    int getRound() const;
    int getEffect() const;

    // ���ٳ����غ���
    void decreaseRound();

    // ��鼼���Ƿ��ڳ���
    bool isActive() const;
};

// ���ӹ������ļ���
class PowerSkill : public Skill {
public:
    PowerSkill();
    void use(Player& player) override;
    void endEffect(Player& player) override;
};

// ���ӷ������ļ���
class DefendSkill : public Skill {
public:
    DefendSkill();
    void use(Player& player) override;
    void endEffect(Player& player) override;
};

// �ظ������ļ���
class HealingSkill : public Skill {
public:
    HealingSkill();
    void use(Player& player) override;
    void applyRoundEffect(Player& player) override;
};

#endif // SKILL_H