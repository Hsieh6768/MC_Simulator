#include "Skill.h"
#include <iostream>

using namespace std;

// Skill 基类实现
Skill::Skill(const string& name, const string& desc, int cost, int cooldown, int level)
    : name(name), description(desc), cost(cost), cooldown(cooldown),
    currentCooldown(0), level(level) {}

void Skill::upgrade() {
    level++;
    cost = static_cast<int>(cost * 0.9); // 升级后消耗减少
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
    cout << "技能: " << name << " (等级 " << level << ")" << endl;
    cout << "描述: " << description << endl;
    cout << "消耗: " << cost << " MP" << endl;
    cout << "冷却: " << cooldown << " 回合";
    if (currentCooldown > 0) {
        cout << " (剩余 " << currentCooldown << " 回合)";
    }
    cout << endl;
}

// AttackSkill 实现
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
    cout << caster.getName() << " 使用了 " << name << "! 造成 " << finalDamage << " 点伤害!" << endl;

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
    cout << "伤害: " << displayDamage << endl;
}

// HealSkill 实现
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

    cout << caster.getName() << " 使用了 " << name << "! 恢复 " << finalHeal << " 点生命值!" << endl;

    return true;
}

void HealSkill::upgrade() {
    Skill::upgrade();
    healAmount = static_cast<int>(healAmount * 1.15);
}

void HealSkill::displayInfo() const {
    Skill::displayInfo();
    int displayHeal = static_cast<int>(healAmount * (1 + (level - 1) * 0.15));
    cout << "治疗: " << displayHeal << " HP" << endl;
}

// BuffSkill 实现
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

    cout << caster.getName() << " 使用了 " << name << "! ";
    cout << "攻击+" << finalAtkBonus << " 防御+" << finalDefBonus;
    cout << " (持续 " << duration << " 回合)" << endl;

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
    cout << "增益: 攻击+" << displayAtk << " 防御+" << displayDef << endl;
    cout << "持续: " << duration << " 回合" << endl;
}

// SkillManager 实现
Skill* SkillManager::createSkill(const string& skillType, int level) {
    if (skillType == "fireball") {
        AttackSkill* skill = new AttackSkill("火球术", "发射一个火球攻击敌人", 15, 2, 20, 1.2);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    else if (skillType == "heal") {
        HealSkill* skill = new HealSkill("治疗术", "恢复自身生命值", 20, 3, 30);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    else if (skillType == "powerup") {
        BuffSkill* skill = new BuffSkill("力量强化", "提升攻击力和防御力", 25, 4, 3, 5, 3);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    return nullptr;
}