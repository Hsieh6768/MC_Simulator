#include "Skill.h"
#include "Player.h"
#include "Monster.h"
#include <iostream>

using namespace std;

// Skill 基类实现
Skill::Skill(const string& name, const string& desc, int cost, int cooldown)
    : name(name), description(desc), cost(cost), cooldown(cooldown),
    currentCooldown(0) {}

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
bool Skill::isReady() const { return currentCooldown == 0; }

void Skill::displayInfo() const {
    ColorManager::COLOR_PRINT("技能: ", BLUE);
    cout << name;
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
    int cost, int cooldown, int damage)
    : Skill(name, desc, cost, cooldown), damage(damage) {}

bool AttackSkill::use(Player& caster, Monster& target) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    target.setHealthCur(max(0, target.getHealthCur() - damage));

    cout << caster.getName() << " 使用了 ";
    ColorManager::COLOR_PRINT(name, RED);
    cout << "! 造成 " << damage << " 点伤害!" << endl;
    Sleep(1200);

    return true;
}

void AttackSkill::displayInfo() const {
    Skill::displayInfo();
    ColorManager::COLOR_PRINT("\n描述: ", RED);
    ColorManager::COLOR_PRINT(description, RED);
    ColorManager::COLOR_PRINT("\n伤害: ", RED);
    cout << damage << endl;
}

// HealSkill 实现
HealSkill::HealSkill(const string& name, const string& desc,
    int cost, int cooldown, int healAmount)
    : Skill(name, desc, cost, cooldown), healAmount(healAmount) {}

bool HealSkill::use(Player& caster, Monster& target) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();

    caster.setHealthCur(min(caster.getHealthCur() + healAmount, caster.getHealthMax()));

    cout << caster.getName() << " 使用了 ";
    ColorManager::COLOR_PRINT(name, GREEN);
    cout << "! 恢复 " << healAmount << " 点生命值!" << endl;
    Sleep(1200);

    return true;
}

void HealSkill::displayInfo() const {
    Skill::displayInfo();
    ColorManager::COLOR_PRINT("\n描述: ", GREEN);
    ColorManager::COLOR_PRINT(description, GREEN);
    ColorManager::COLOR_PRINT("\n治疗: ", GREEN);
    cout << healAmount;
    ColorManager::COLOR_PRINT(" HP\n", GREEN);
}

// BuffSkill 实现
BuffSkill::BuffSkill(const string& name, const string& desc,
    int cost, int cooldown, int duration, int atkBonus, int defBonus)
    : Skill(name, desc, cost, cooldown), duration(duration),
    attackBonus(atkBonus), defenseBonus(defBonus) {}

bool BuffSkill::use(Player& caster, Monster& target) {
    if (!isReady() || caster.getMagicPowerCur() < cost) {
        return false;
    }

    caster.setMagicPowerCur(caster.getMagicPowerCur() - cost);
    resetCooldown();


    caster.setPlayerBuff({ attackBonus, defenseBonus, duration });

    cout << caster.getName() << " 使用了 ";
    ColorManager::COLOR_PRINT(name, BLUE);
    cout << "! 攻击+" << attackBonus << " 防御+" << defenseBonus;
    cout << " (持续 " << duration << " 回合)" << endl;
    Sleep(1200);

    return true;
}


void BuffSkill::displayInfo() const {
    Skill::displayInfo();
    ColorManager::COLOR_PRINT("\n描述: ", PURPLE);
    ColorManager::COLOR_PRINT(description, PURPLE);
    ColorManager::COLOR_PRINT("\n增益: 攻击+ ", PURPLE);
    cout << attackBonus;
    ColorManager::COLOR_PRINT(", 防御+ ", PURPLE);
    cout << defenseBonus;
    ColorManager::COLOR_PRINT("\t持续: ", PURPLE);
    cout << duration;
    ColorManager::COLOR_PRINT(" 回合\n", PURPLE);
}

// SkillManager 实现
std::unique_ptr<Skill> SkillManager::createSkill(const string& skillType) {
    if (skillType == "fireball") {
        auto skill = std::make_unique<AttackSkill>("火球术", "发射一个火球攻击敌人", 4, 2, 20);
        return skill;
    }
    else if (skillType == "heal") {
        auto skill = std::make_unique<HealSkill>("治疗术", "恢复自身生命值", 2, 3, 5);
        return skill;
    }
    else if (skillType == "powerup") {
        auto skill = std::make_unique<BuffSkill>("力量强化", "提升攻击力和防御力", 3, 4, 3, 5, 3);
        return skill;
    }
    return nullptr;
}