#ifndef SKILL_H
#define SKILL_H

#include <string>
#include "Player.h"

class Skill {
protected:
    std::string name;
    std::string description;
    int cost;           // ħ������
    int cooldown;       // ��ȴ�غ�
    int currentCooldown;// ��ǰ��ȴ
    int level;          // ���ܵȼ�

public:
    Skill(const std::string& name = "", const std::string& desc = "",
        int cost = 0, int cooldown = 0, int level = 1);
    virtual ~Skill() = default;

    // ʹ�ü��ܣ����麯����
    virtual bool use(Player& caster) = 0;

    // ��������
    virtual void upgrade();

    // ��ȴ����
    void reduceCooldown();
    void resetCooldown();

    // ��ȡ��Ϣ
    std::string getName() const;
    std::string getDescription() const;
    int getCost() const;
    int getCooldown() const;
    int getCurrentCooldown() const;
    int getLevel() const;
    bool isReady() const;

    // ��ʾ������Ϣ
    virtual void displayInfo() const;
};

// ��������
class AttackSkill : public Skill {
private:
    int damage;
    double multiplier;  // ��������

public:
    AttackSkill(const std::string& name, const std::string& desc,
        int cost, int cooldown, int damage, double multiplier = 1.0);

    bool use(Player& caster) override;
    void upgrade() override;
    void displayInfo() const override;
};

// ���Ƽ���
class HealSkill : public Skill {
private:
    int healAmount;

public:
    HealSkill(const std::string& name, const std::string& desc,
        int cost, int cooldown, int healAmount);

    bool use(Player& caster) override;
    void upgrade() override;
    void displayInfo() const override;
};

// ���漼��
class BuffSkill : public Skill {
private:
    int duration;
    int attackBonus;
    int defenseBonus;

public:
    BuffSkill(const std::string& name, const std::string& desc,
        int cost, int cooldown, int duration, int atkBonus, int defBonus);

    bool use(Player& caster) override;
    void upgrade() override;
    void displayInfo() const override;
};

// ���ܹ�����
class SkillManager {
public:
    static Skill* createSkill(const std::string& skillType, int level = 1);
};

#endif // SKILL_H