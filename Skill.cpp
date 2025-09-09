#include "Skill.h"
#include <iostream>

using namespace std;

// Skill ����ʵ��
Skill::Skill(const string& name, const string& desc, int cost, int cooldown, int level)
    : name(name), description(desc), cost(cost), cooldown(cooldown),
    currentCooldown(0), level(level) {}

void Skill::upgrade() {
    level++;
    cost = static_cast<int>(cost * 0.9); // ���������ļ���
}

void Skill::reduceCooldown() {
    if (currentCooldown > 0) {
        currentCooldown--;
    }
}

void Skill::resetCooldown() {
    currentCooldown = cooldown;
}

string Skill::getName() const { return name; }
string Skill::getDescription() const { return description; }
int Skill::getCost() const { return cost; }
int Skill::getCooldown() const { return cooldown; }
int Skill::getCurrentCooldown() const { return currentCooldown; }
int Skill::getLevel() const { return level; }
bool Skill::isReady() const { return currentCooldown == 0; }

void Skill::displayInfo() const {
    cout << "����: " << name << " (�ȼ� " << level << ")" << endl;
    cout << "����: " << description << endl;
    cout << "����: " << cost << " MP" << endl;
    cout << "��ȴ: " << cooldown << " �غ�";
    if (currentCooldown > 0) {
        cout << " (ʣ�� " << currentCooldown << " �غ�)";
    }
    cout << endl;
}

// AttackSkill ʵ��
AttackSkill::AttackSkill(const string& name, const string& desc,
    int cost, int cooldown, int damage, double multiplier)
    : Skill(name, desc, cost, cooldown, 1), damage(damage), multiplier(multiplier) {}

bool AttackSkill::use(Player& caster) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    int finalDamage = static_cast<int>(damage * multiplier * (1 + (level - 1) * 0.1));
    cout << caster.getName() << " ʹ���� " << name << "! ��� " << finalDamage << " ���˺�!" << endl;

    return true;
}

void AttackSkill::upgrade() {
    Skill::upgrade();
    damage = static_cast<int>(damage * 1.2);
    multiplier += 0.1;
}

void AttackSkill::displayInfo() const {
    Skill::displayInfo();
    int displayDamage = static_cast<int>(damage * multiplier * (1 + (level - 1) * 0.1));
    cout << "�˺�: " << displayDamage << endl;
}

// HealSkill ʵ��
HealSkill::HealSkill(const string& name, const string& desc,
    int cost, int cooldown, int healAmount)
    : Skill(name, desc, cost, cooldown, 1), healAmount(healAmount) {}

bool HealSkill::use(Player& caster) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    int finalHeal = static_cast<int>(healAmount * (1 + (level - 1) * 0.15));
    caster.setHealthCur(min(caster.getHealthCur() + finalHeal, caster.getHealthMax()));

    cout << caster.getName() << " ʹ���� " << name << "! �ָ� " << finalHeal << " ������ֵ!" << endl;

    return true;
}

void HealSkill::upgrade() {
    Skill::upgrade();
    healAmount = static_cast<int>(healAmount * 1.15);
}

void HealSkill::displayInfo() const {
    Skill::displayInfo();
    int displayHeal = static_cast<int>(healAmount * (1 + (level - 1) * 0.15));
    cout << "����: " << displayHeal << " HP" << endl;
}

// BuffSkill ʵ��
BuffSkill::BuffSkill(const string& name, const string& desc,
    int cost, int cooldown, int duration, int atkBonus, int defBonus)
    : Skill(name, desc, cost, cooldown, 1), duration(duration),
    attackBonus(atkBonus), defenseBonus(defBonus) {}

bool BuffSkill::use(Player& caster) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    int finalAtkBonus = static_cast<int>(attackBonus * (1 + (level - 1) * 0.1));
    int finalDefBonus = static_cast<int>(defenseBonus * (1 + (level - 1) * 0.1));

    caster.setAttack(caster.getAttack() + finalAtkBonus);
    caster.setDefense(caster.getDefense() + finalDefBonus);

    cout << caster.getName() << " ʹ���� " << name << "! ";
    cout << "����+" << finalAtkBonus << " ����+" << finalDefBonus;
    cout << " (���� " << duration << " �غ�)" << endl;

    return true;
}

void BuffSkill::upgrade() {
    Skill::upgrade();
    attackBonus = static_cast<int>(attackBonus * 1.1);
    defenseBonus = static_cast<int>(defenseBonus * 1.1);
}

void BuffSkill::displayInfo() const {
    Skill::displayInfo();
    int displayAtk = static_cast<int>(attackBonus * (1 + (level - 1) * 0.1));
    int displayDef = static_cast<int>(defenseBonus * (1 + (level - 1) * 0.1));
    cout << "����: ����+" << displayAtk << " ����+" << displayDef << endl;
    cout << "����: " << duration << " �غ�" << endl;
}

// SkillManager ʵ��
Skill* SkillManager::createSkill(const string& skillType, int level) {
    if (skillType == "fireball") {
        AttackSkill* skill = new AttackSkill("������", "����һ�����򹥻�����", 15, 2, 20, 1.2);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    else if (skillType == "heal") {
        HealSkill* skill = new HealSkill("������", "�ָ���������ֵ", 20, 3, 30);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    else if (skillType == "powerup") {
        BuffSkill* skill = new BuffSkill("����ǿ��", "�����������ͷ�����", 25, 4, 3, 5, 3);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    return nullptr;
}