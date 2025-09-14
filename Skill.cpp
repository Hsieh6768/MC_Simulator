#include "Skill.h"
#include "Player.h"
#include "Monster.h"
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
    ColorManager::COLOR_PRINT("技能: ", BLUE);
    cout << name;
    ColorManager::COLOR_PRINT(" (等级 ", BLUE);
    cout << level;
    ColorManager::COLOR_PRINT(")", BLUE);

    ColorManager::COLOR_PRINT("\n消耗: ", BLUE);
    cout << cost;
    ColorManager::COLOR_PRINT(" MP", BLUE);

    ColorManager::COLOR_PRINT("\t冷却: ", BLUE);
    cout << cooldown;
    ColorManager::COLOR_PRINT(" 回合", BLUE);
    if (currentCooldown > 0) {
        ColorManager::COLOR_PRINT(" (剩余 ", BLUE);
        cout << currentCooldown;
        ColorManager::COLOR_PRINT(" 回合)", BLUE);
    }
}

// AttackSkill 实现
AttackSkill::AttackSkill(const string& name, const string& desc,
    int cost, int cooldown, int damage, double multiplier)
    : Skill(name, desc, cost, cooldown, 1), damage(damage), multiplier(multiplier) {}

bool AttackSkill::use(Player& caster, Monster& target) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    int finalDamage = static_cast<int>(damage * multiplier * (1 + (level - 1) * 0.1));
    target.setHealthCur(max(0, target.getHealthCur() - finalDamage));

    cout << caster.getName() << " 使用了 ";
    ColorManager::COLOR_PRINT(name, RED);
    cout << "! 造成 " << finalDamage << " 点伤害!" << endl;
    Sleep(1200);

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
    ColorManager::COLOR_PRINT("\n描述: ", RED);
    ColorManager::COLOR_PRINT(description, RED);
    ColorManager::COLOR_PRINT("\n伤害: ", RED);
    cout << displayDamage << endl;
}

// HealSkill 实现
HealSkill::HealSkill(const string& name, const string& desc,
    int cost, int cooldown, int healAmount)
    : Skill(name, desc, cost, cooldown, 1), healAmount(healAmount) {}

bool HealSkill::use(Player& caster, Monster& target) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    int finalHeal = static_cast<int>(healAmount * (1 + (level - 1) * 0.15));
    caster.setHealthCur(min(caster.getHealthCur() + finalHeal, caster.getHealthMax()));

    cout << caster.getName() << " 使用了 ";
    ColorManager::COLOR_PRINT(name, GREEN);
    cout << "! 恢复 " << finalHeal << " 点生命值!" << endl;
    Sleep(1200);

    return true;
}

void HealSkill::upgrade() {
    Skill::upgrade();
    healAmount = static_cast<int>(healAmount * 1.15);
}

void HealSkill::displayInfo() const {
    Skill::displayInfo();
    int displayHeal = static_cast<int>(healAmount * (1 + (level - 1) * 0.15));
    ColorManager::COLOR_PRINT("\n描述: ", GREEN);
    ColorManager::COLOR_PRINT(description, GREEN);
    ColorManager::COLOR_PRINT("\n治疗: ", GREEN);
    cout << displayHeal;
    ColorManager::COLOR_PRINT(" HP\n", GREEN);
}

// BuffSkill 实现
BuffSkill::BuffSkill(const string& name, const string& desc,
    int cost, int cooldown, int duration, int atkBonus, int defBonus)
    : Skill(name, desc, cost, cooldown, 1), duration(duration),
    attackBonus(atkBonus), defenseBonus(defBonus) {}

bool BuffSkill::use(Player& caster, Monster& target) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    int finalAtkBonus = static_cast<int>(attackBonus * (1 + (level - 1) * 0.1));
    int finalDefBonus = static_cast<int>(defenseBonus * (1 + (level - 1) * 0.1));

    caster.setPlayerBuff({ finalAtkBonus, finalDefBonus, duration });

    cout << caster.getName() << " 使用了 ";
    ColorManager::COLOR_PRINT(name, BLUE);
    cout << "! 攻击+" << finalAtkBonus << " 防御+" << finalDefBonus;
    cout << " (持续 " << duration << " 回合)" << endl;
    Sleep(1200);

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
    ColorManager::COLOR_PRINT("\n描述: ", PURPLE);
    ColorManager::COLOR_PRINT(description, PURPLE);
    ColorManager::COLOR_PRINT("\n增益: 攻击+ ", PURPLE);
    cout << displayAtk;
    ColorManager::COLOR_PRINT(", 防御+ ", PURPLE);
    cout << displayDef;
    ColorManager::COLOR_PRINT("\t持续: ", PURPLE);
    cout << duration;
    ColorManager::COLOR_PRINT(" 回合\n", PURPLE);
}

// SkillManager 实现
std::unique_ptr<Skill> SkillManager::createSkill(const string& skillType, int level) {
    if (skillType == "fireball") {
        auto skill = std::make_unique<AttackSkill>("火球术", "发射一个火球攻击敌人", 4, 2, 20, 1.2);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    else if (skillType == "heal") {
        auto skill = std::make_unique<HealSkill>("治疗术", "恢复自身生命值", 2, 3, 5);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    else if (skillType == "powerup") {
        auto skill = std::make_unique<BuffSkill>("力量强化", "提升攻击力和防御力", 3, 4, 3, 5, 3);
        for (int i = 1; i < level; i++) skill->upgrade();
        return skill;
    }
    return nullptr;
}