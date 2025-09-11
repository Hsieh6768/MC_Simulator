#include "Command.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include "Skill.h"

using namespace std;

Command::Command(Player& player, Map& map) : player(player), map(map) {
    srand(time(0));
}

void Command::NewGame() {
    // 初始化玩家属性
    player = Player(
        "史蒂夫",    // 名称
        20,         // 最大生命值
        20,         // 当前生命值
        2,          // 基础攻击力
        0,          // 基础防御力
        5,          // 最大魔力值
        5,          // 当前魔力值
        0,          // 初始绿宝石
        Weapon(),   // 初始武器
        Armor(),    // 初始护甲
        {},         // 初始技能
        { 0, 0, 0 } // 初始增益效果
    );

    // 添加初始技能
    player.addSkill(SkillManager::createSkill("fireball", 1));
    player.addSkill(SkillManager::createSkill("heal", 1));
    player.addSkill(SkillManager::createSkill("powerup", 1));

    // 初始化地图
    map = Map();

    cout << "新游戏已创建！祝你冒险愉快！" << endl;
}

bool Command::SaveGame(const std::string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "无法创建存档文件: " << filename << endl;
        return false;
    }

    try {
        // 序列化玩家数据
        serializePlayer(outFile);

        // 序列化地图数据
        serializeMap(outFile);

        outFile.close();
        cout << "游戏已保存至: " << filename << endl;
        return true;
    }
    catch (...) {
        cerr << "保存游戏时发生错误" << endl;
        outFile.close();
        return false;
    }
}

bool Command::LoadGame(const std::string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "无法读取存档文件: " << filename << endl;
        return false;
    }

    try {
        // 反序列化玩家数据
        deserializePlayer(inFile);

        // 反序列化地图数据
        deserializeMap(inFile);

        inFile.close();
        cout << "游戏已从 " << filename << " 加载" << endl;
        return true;
    }
    catch (...) {
        cerr << "加载游戏时发生错误" << endl;
        inFile.close();
        return false;
    }
}

void Command::Trade() {
    if (!isInBlacksmith()) {
        cout << "你需要在铁匠铺才能进行交易！" << endl;
        return;
    }

    cout << "欢迎来到铁匠铺！" << endl;
    cout << "你目前的装备: " << endl;
    player.getWeapon().displayInfo();
    player.getArmor().displayInfo();
    cout << "\n你有 " << player.getMoney() << " 绿宝石" << endl;

    int choice;
    bool shopping = true;

    while (shopping) {
        cout << "\n请选择要购买的类型:" << endl;
        cout << "1. 武器" << endl;
        cout << "2. 护甲" << endl;
        cout << "0. 离开商店" << endl;
        cout << "请选择: ";
        cin >> choice;

        switch (choice) {
        case 1:
        {
            cout << "\n可购买的武器:" << endl;
            cout << "1. " << EquipmentTypes::WOODEN_SWORD.getName() << " (攻击+"
                << EquipmentTypes::WOODEN_SWORD.getAttack() << ") - "
                << EquipmentTypes::WOODEN_SWORD.getValue() << " 绿宝石" << endl;
            cout << "2. " << EquipmentTypes::IRON_SWORD.getName() << " (攻击+"
                << EquipmentTypes::IRON_SWORD.getAttack() << ") - "
                << EquipmentTypes::IRON_SWORD.getValue() << " 绿宝石" << endl;
            cout << "3. " << EquipmentTypes::DIAMOND_SWORD.getName() << " (攻击+"
                << EquipmentTypes::DIAMOND_SWORD.getAttack() << ") - "
                << EquipmentTypes::DIAMOND_SWORD.getValue() << " 绿宝石" << endl;
            cout << "0. 返回" << endl;

            int weaponChoice;
            cout << "请选择武器: ";
            cin >> weaponChoice;

            if (weaponChoice == 0) break;

            Weapon selectedWeapon;
            int weaponCost = 0;

            switch (weaponChoice) {
            case 1:
                selectedWeapon = EquipmentTypes::WOODEN_SWORD;
                weaponCost = EquipmentTypes::WOODEN_SWORD.getValue();
                break;
            case 2:
                selectedWeapon = EquipmentTypes::IRON_SWORD;
                weaponCost = EquipmentTypes::IRON_SWORD.getValue();
                break;
            case 3:
                selectedWeapon = EquipmentTypes::DIAMOND_SWORD;
                weaponCost = EquipmentTypes::DIAMOND_SWORD.getValue();
                break;
            default:
                cout << "无效的选择！" << endl;
                continue;
            }

            if (player.getMoney() >= weaponCost) {
                player.setWeapon(selectedWeapon);
                player.setMoney(player.getMoney() - weaponCost);
                cout << "购买成功！装备了 " << selectedWeapon.getName() << endl;
            }
            else {
                cout << "绿宝石不足！" << endl;
            }
        }
        break;

        case 2:
        {
            cout << "\n可购买的护甲:" << endl;
            cout << "1. " << EquipmentTypes::LEATHER_ARMOR.getName() << " (防御+"
                << EquipmentTypes::LEATHER_ARMOR.getDefense() << ") - "
                << EquipmentTypes::LEATHER_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "2. " << EquipmentTypes::IRON_ARMOR.getName() << " (防御+"
                << EquipmentTypes::IRON_ARMOR.getDefense() << ") - "
                << EquipmentTypes::IRON_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "3. " << EquipmentTypes::DIAMOND_ARMOR.getName() << " (防御+"
                << EquipmentTypes::DIAMOND_ARMOR.getDefense() << ") - "
                << EquipmentTypes::DIAMOND_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "0. 返回" << endl;

            int armorChoice;
            cout << "请选择护甲: ";
            cin >> armorChoice;

            if (armorChoice == 0) break;

            Armor selectedArmor;
            int armorCost = 0;

            switch (armorChoice) {
            case 1:
                selectedArmor = EquipmentTypes::LEATHER_ARMOR;
                armorCost = EquipmentTypes::LEATHER_ARMOR.getValue();
                break;
            case 2:
                selectedArmor = EquipmentTypes::IRON_ARMOR;
                armorCost = EquipmentTypes::IRON_ARMOR.getValue();
                break;
            case 3:
                selectedArmor = EquipmentTypes::DIAMOND_ARMOR;
                armorCost = EquipmentTypes::DIAMOND_ARMOR.getValue();
                break;
            default:
                cout << "无效的选择！" << endl;
                continue;
            }

            if (player.getMoney() >= armorCost) {
                player.setArmor(selectedArmor);
                player.setMoney(player.getMoney() - armorCost);
                cout << "购买成功！装备了 " << selectedArmor.getName() << endl;
            }
            else {
                cout << "绿宝石不足！" << endl;
            }
        }
        break;

        case 0:
            shopping = false;
            cout << "欢迎下次光临！" << endl;
            break;

        default:
            cout << "无效选择！" << endl;
        }
    }
}

void Command::Recover() {
    if (!isInVillage()) {
        cout << "你需要在村庄才能恢复状态！" << endl;
        return;
    }

    int cost = 3;
    cout << "村庄治疗师可以恢复你的状态，需要 " << cost << " 绿宝石" << endl;
    cout << "你目前有 " << player.getMoney() << " 绿宝石" << endl;

    if (player.getMoney() >= cost) {
        player.setHealthCur(player.getHealthMax());
        player.setMagicPowerCur(player.getMagicPowerMax());
        player.setMoney(player.getMoney() - cost);
        cout << "状态已完全恢复！" << endl;
    }
    else {
        cout << "绿宝石不足！" << endl;
    }
}

void Command::BattleSelection() {
    auto monsters = map.getMonstersInCurrentArea();
    if (monsters.empty()) {
        cout << "当前区域没有怪物！" << endl;
        return;
    }

    cout << "选择要战斗的怪物:" << endl;
    for (size_t i = 0; i < monsters.size(); i++) {
        cout << i + 1 << ". " << monsters[i]->getName() << " (生命: "
            << monsters[i]->getHealthCur() << "/" << monsters[i]->getHealthMax() << ")" << endl;
    }
    cout << "0. 取消" << endl;

    int choice;
    cout << "请选择: ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(monsters.size())) {
        auto selectedMonster = monsters[choice - 1];
        Battle battle(player, *selectedMonster);
        battle.start();

        // 战斗后检查怪物是否被击败
        if (selectedMonster->getHealthCur() <= 0) {
            // 从地图中移除被击败的怪物
            map.removeCreatureFromArea(map.getCurrentAreaId(), selectedMonster->getName());
        }
    }
    else if (choice != 0) {
        cout << "无效选择！" << endl;
    }
}

void Command::Move() {
    auto connectedAreas = map.getConnectedAreas();
    if (connectedAreas.empty()) {
        cout << "没有可前往的区域！" << endl;
        return;
    }

    cout << "可前往的区域:" << endl;
    for (size_t i = 0; i < connectedAreas.size(); i++) {
        Area* area = map.getArea(connectedAreas[i]);
        if (area) {
            cout << i + 1 << ". " << area->name;
            if (area->isSafe) cout << " (安全区)";
            cout << endl;
        }
    }
    cout << "0. 取消" << endl;

    int choice;
    cout << "请选择: ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(connectedAreas.size())) {
        if (map.moveToConnectedArea(choice - 1)) {
            cout << "已移动到: " << map.getCurrentArea()->name << endl;
            map.displayCurrentPosition();
        }
        else {
            cout << "移动失败！" << endl;
        }
    }
    else if (choice != 0) {
        cout << "无效选择！" << endl;
    }
}

void Command::Panel() {
    cout << "========== 玩家属性 ==========" << endl;
    cout << player.getName() << endl;
    player.showInfo();

    cout << "武器: " << player.getWeapon().getName() << endl;
    player.getWeapon().displayInfo();

    cout << "护甲: " << player.getArmor().getName() << endl;
    player.getArmor().displayInfo();

    cout << "技能:" << endl;
    for (const auto& skill : player.getSkill()) {
        skill->displayInfo();
        cout << "------------------------" << endl;
    }
    cout << "==============================" << endl;
}

bool Command::isInBlacksmith() const {
    Area* currentArea = map.getCurrentArea();
    return currentArea && currentArea->type == BLACKSMITH;
}

bool Command::isInVillage() const {
    Area* currentArea = map.getCurrentArea();
    return currentArea && currentArea->type == VILLAGE;
}

void Command::serializePlayer(std::ofstream& out) {
    // 写入玩家基本信息
    string name = player.getName();
    out.write(name.c_str(), name.size() + 1);

    int healthMax = player.getHealthMax();
    int healthCur = player.getHealthCur();
    int attack = player.getAttack();
    int defense = player.getDefense();
    int magicMax = player.getMagicPowerMax();
    int magicCur = player.getMagicPowerCur();
    int money = player.getMoney();
    out.write(reinterpret_cast<const char*>(&healthMax), sizeof(int));
    out.write(reinterpret_cast<const char*>(&healthCur), sizeof(int));
    out.write(reinterpret_cast<const char*>(&attack), sizeof(int));
    out.write(reinterpret_cast<const char*>(&defense), sizeof(int));
    out.write(reinterpret_cast<const char*>(&magicMax), sizeof(int));
    out.write(reinterpret_cast<const char*>(&magicCur), sizeof(int));
    out.write(reinterpret_cast<const char*>(&money), sizeof(int));

    // 写入武器信息
    string weaponName = player.getWeapon().getName();
    out.write(weaponName.c_str(), weaponName.size() + 1);

    // 写入护甲信息
    string armorName = player.getArmor().getName();
    out.write(armorName.c_str(), armorName.size() + 1);

    // 写入技能信息
    int skillCount = player.getSkill().size();
    out.write(reinterpret_cast<const char*>(&skillCount), sizeof(int));
    for (const auto& skill : player.getSkill()) {
        string skillName = skill->getName();
        out.write(skillName.c_str(), skillName.size() + 1);
        int level = skill->getLevel();
        out.write(reinterpret_cast<const char*>(&level), sizeof(int));
    }

    // 写入增益状态
    TemporaryBuff buff = player.getTemporaryBuff();
    out.write(reinterpret_cast<const char*>(&buff.attack_bonus), sizeof(int));
    out.write(reinterpret_cast<const char*>(&buff.defense_bonus), sizeof(int));
    out.write(reinterpret_cast<const char*>(&buff.duration), sizeof(int));
}

void Command::serializeMap(std::ofstream& out) {
    // 写入当前区域ID
    int currentAreaId = map.getCurrentAreaId();
    out.write(reinterpret_cast<const char*>(&currentAreaId), sizeof(int));

    // 写入所有区域的访问状态
    int areaCount = 10; // 假设有10个区域
    out.write(reinterpret_cast<const char*>(&areaCount), sizeof(int));

    for (int i = 0; i < areaCount; i++) {
        Area* area = map.getArea(i);
        if (area) {
            bool visited = map.isAreaVisited(i);
            out.write(reinterpret_cast<const char*>(&visited), sizeof(bool));
        }
    }
}

void Command::deserializePlayer(std::ifstream& in) {
    // 读取玩家基本信息
    char nameBuffer[100];
    in.getline(nameBuffer, 100, '\0');
    player.setName(nameBuffer);

    int healthMax = 0;
    int healthCur = 0;
    int attack = 0; 
    int defense = 0;
    int magicMax = 0; 
    int magicCur = 0;
    int money = 0;
    in.read(reinterpret_cast<char*>(&healthMax), sizeof(int));
    in.read(reinterpret_cast<char*>(&healthCur), sizeof(int));
    in.read(reinterpret_cast<char*>(&attack), sizeof(int));
    in.read(reinterpret_cast<char*>(&defense), sizeof(int));
    in.read(reinterpret_cast<char*>(&magicMax), sizeof(int));
    in.read(reinterpret_cast<char*>(&magicCur), sizeof(int));
    in.read(reinterpret_cast<char*>(&money), sizeof(int));

    player.setHealthMax(healthMax);
    player.setHealthCur(healthCur);
    player.setAttack(attack);
    player.setDefense(defense);
    player.setMagicPowerMax(magicMax);
    player.setMagicPowerCur(magicCur);
    player.setMoney(money);

    // 读取装备信息
    char equipBuffer[100];
    in.getline(equipBuffer, 100, '\0');
    string equipName(equipBuffer);

    // 根据装备名称设置装备
    if (equipName == EquipmentTypes::WOODEN_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::WOODEN_SWORD);
    }
    else if (equipName == EquipmentTypes::IRON_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::IRON_SWORD);
    }
    else if (equipName == EquipmentTypes::DIAMOND_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::DIAMOND_SWORD);
    }
    else if (equipName == EquipmentTypes::LEATHER_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::LEATHER_ARMOR);
    }
    else if (equipName == EquipmentTypes::IRON_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::IRON_ARMOR);
    }
    else if (equipName == EquipmentTypes::DIAMOND_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::DIAMOND_ARMOR);
    }

    // 读取技能信息
    int skillCount = 0;
    in.read(reinterpret_cast<char*>(&skillCount), sizeof(int));

    player.clearSkills();
    for (int i = 0; i < skillCount; i++) {
        char skillBuffer[100];
        in.getline(skillBuffer, 100, '\0');
        string skillName(skillBuffer);

        int level = 1;
        in.read(reinterpret_cast<char*>(&level), sizeof(int));

        if (skillName == "火球术") {
            player.addSkill(SkillManager::createSkill("fireball", level));
        }
        else if (skillName == "治疗术") {
            player.addSkill(SkillManager::createSkill("heal", level));
        }
        else if (skillName == "力量强化") {
            player.addSkill(SkillManager::createSkill("powerup", level));
        }
    }

    // 读取增益状态
    TemporaryBuff buff = { 0, 0, 0 };
    in.read(reinterpret_cast<char*>(&buff.attack_bonus), sizeof(int));
    in.read(reinterpret_cast<char*>(&buff.defense_bonus), sizeof(int));
    in.read(reinterpret_cast<char*>(&buff.duration), sizeof(int));
    player.setTemporaryBuff(buff);
}

void Command::deserializeMap(std::ifstream& in) {
    // 读取当前区域ID
    int currentAreaId = 0;
    in.read(reinterpret_cast<char*>(&currentAreaId), sizeof(int));
    map.moveToArea(currentAreaId);

    // 读取所有区域的访问状态
    int areaCount = 0;
    in.read(reinterpret_cast<char*>(&areaCount), sizeof(int));

    for (int i = 0; i < areaCount; i++) {
        bool visited = false;
        in.read(reinterpret_cast<char*>(&visited), sizeof(bool));

        if (visited) {
            map.markAreaVisited(i);
        }
    }

    // 重新生成怪物
    map.spawnFixedMonsters();
}