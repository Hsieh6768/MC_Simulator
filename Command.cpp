#include "Command.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Skill.h"

using namespace std;

Command::Command(Player& player, Map& map) : player(player), map(map) {
    srand(static_cast<unsigned int>(time(0)));
}

void Command::newGame() {
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

bool Command::saveGame(const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "无法创建存档文件: " << filename << endl;
        Sleep(1200);
        return false;
    }

    try {
        // 序列化玩家数据
        serializePlayer(outFile);

        // 序列化地图数据
        serializeMap(outFile);

        outFile.close();
        cout << "游戏已保存至: " << filename << endl;
        Sleep(1200);
        return true;
    }
    catch (...) {
        cerr << "保存游戏时发生错误" << endl;
        Sleep(1200);
        outFile.close();
        return false;
    }
}

bool Command::loadGame(const string& filename) {
    system("cls");
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "无法读取存档文件: " << filename << endl;
        Sleep(1200);
        return false;
    }

    try {
        // 反序列化玩家数据
        deserializePlayer(inFile);

        // 反序列化地图数据
        deserializeMap(inFile);

        inFile.close();
        cout << "游戏已从 " << filename << " 加载" << endl;
        Sleep(1200);
        return true;
    }
    catch (...) {
        cerr << "加载游戏时发生错误" << endl;
        Sleep(1200);
        inFile.close();
        return false;
    }
}

void Command::exitGame() {
    cout << "正在保存游戏并退出..." << endl;
    if (saveGame("Mc_Simulator.txt")) {
        cout << "游戏已自动保存。" << endl;
    }
    else {
        cout << "自动保存失败，是否仍要退出？(y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "取消退出。" << endl;
            return;
        }
    }
    cout << "感谢游玩！再见！" << endl;
    exit(0);
}

bool Command::autoSave() {
    return saveGame("autosave.txt");
}

void Command::trade() {
    if (!isInBlacksmith()) {
        cout << "你需要在铁匠铺才能进行交易！" << endl;
        Sleep(1200);
        return;
    }

    cout << "欢迎来到铁匠铺！" << endl;
    cout << "你目前的装备: " << endl;
    player.getWeapon().displayInfo();
    player.getArmor().displayInfo();
    cout << "\n你有 " << player.getMoney() << " 绿宝石" << endl << endl;

    int choice;
    bool shopping = true;

    while (shopping) {
        cout << "请选择要购买的类型:" << endl;
        cout << "1. 武器";
        cout << "\t2. 护甲";
        cout << "\t3. 离开商店" << endl;
        cout << "请选择: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
        {
            system("cls");
            cout << "可购买的武器:" << endl;
            cout << "1. " << EquipmentTypes::WOODEN_SWORD.getName() << " (攻击+"
                << EquipmentTypes::WOODEN_SWORD.getAttack() << ") - "
                << EquipmentTypes::WOODEN_SWORD.getValue() << " 绿宝石" << endl;
            cout << "2. " << EquipmentTypes::IRON_SWORD.getName() << " (攻击+"
                << EquipmentTypes::IRON_SWORD.getAttack() << ") - "
                << EquipmentTypes::IRON_SWORD.getValue() << " 绿宝石" << endl;
            cout << "3. " << EquipmentTypes::DIAMOND_SWORD.getName() << " (攻击+"
                << EquipmentTypes::DIAMOND_SWORD.getAttack() << ") - "
                << EquipmentTypes::DIAMOND_SWORD.getValue() << " 绿宝石" << endl;
            cout << "4. 返回" << endl;

            int weaponChoice;
            cout << "请选择武器: ";
            cin >> weaponChoice;

            if (weaponChoice == 4) {
                system("cls");
                break;
            }

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
                system("cls");
                cout << "无效的选择！" << endl;
                Sleep(1200);
                continue;
            }

            if (player.getMoney() >= weaponCost) {
                system("cls");
                player.setWeapon(selectedWeapon);
                player.setMoney(player.getMoney() - weaponCost);
                cout << "购买成功！装备了 " << selectedWeapon.getName() << endl;
            }
            else {
                system("cls");
                cout << "绿宝石不足！" << endl;
            }
        }
        Sleep(1200);
        system("cls");
        break;

        case 2:
        {
            system("cls");
            cout << "可购买的护甲:" << endl;
            cout << "1. " << EquipmentTypes::LEATHER_ARMOR.getName() << " (防御+"
                << EquipmentTypes::LEATHER_ARMOR.getDefense() << ") - "
                << EquipmentTypes::LEATHER_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "2. " << EquipmentTypes::IRON_ARMOR.getName() << " (防御+"
                << EquipmentTypes::IRON_ARMOR.getDefense() << ") - "
                << EquipmentTypes::IRON_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "3. " << EquipmentTypes::DIAMOND_ARMOR.getName() << " (防御+"
                << EquipmentTypes::DIAMOND_ARMOR.getDefense() << ") - "
                << EquipmentTypes::DIAMOND_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "4. 返回" << endl;

            int armorChoice;
            cout << "请选择护甲: ";
            cin >> armorChoice;

            if (armorChoice == 4) {
                system("cls");
                break;
            }

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
                system("cls");
                cout << "无效的选择！" << endl;
                Sleep(1200);
                continue;
            }

            if (player.getMoney() >= armorCost) {
                system("cls");
                player.setArmor(selectedArmor);
                player.setMoney(player.getMoney() - armorCost);
                cout << "购买成功！装备了 " << selectedArmor.getName() << endl;
            }
            else {
                system("cls");
                cout << "绿宝石不足！" << endl;
            }
        }
        Sleep(1200);
        system("cls");
        break;

        case 3:
            system("cls");
            shopping = false;
            cout << "欢迎下次光临！" << endl;
            Sleep(1200);
            break;

        default:
            system("cls");
            cout << "无效选择！" << endl;
            Sleep(1200);
            system("cls");
        }
    }
}

void Command::recover() {
    if (!isInVillage()) {
        cout << "你需要在村庄才能恢复状态！" << endl;
        Sleep(1200);
        return;
    }

    cout << "在村庄的床上休息可以恢复你的状态" << endl;
    cout << "是否开始睡眠？(y/n): ";
    char choice = 'n';
    cin >> choice;

    system("cls");
    if (choice == 'Y' || choice == 'y') {
        cout << "----- 睡眠中 -----" << endl;
        Sleep(5000);
        player.setHealthCur(player.getHealthMax());
        player.setMagicPowerCur(player.getMagicPowerMax());
        cout << "\n状态已完全恢复！" << endl;
        Sleep(1200);
    }
    else {
        cout << "欢迎下次光临！" << endl;
        Sleep(1200);
    }
    system("cls");
}

void Command::battleSelection() {
    auto monsters = map.getMonstersInCurrentArea();
    if (monsters.empty()) {
        cout << "当前区域没有怪物！" << endl;
        Sleep(1200);
        return;
    }

    cout << "选择要战斗的怪物:" << endl;
    for (size_t i = 0; i < monsters.size(); i++) {
        cout << i + 1 << ". " << monsters[i]->getName() << endl;
        monsters[i]->showInfo();
        cout << endl;
    }
    cout << "0. 取消" << endl;

    int choice;
    cout << "请选择: ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(monsters.size())) {
        system("cls");

        // 在战斗开始前自动保存
        if (autoSave()) {
            cout << "游戏已自动保存，准备进入战斗..." << endl;
            Sleep(1200);
        }
        else {
            cout << "自动保存失败，是否继续战斗？(y/n): ";
            char confirm = 'n';
            cin >> confirm;
            if (confirm != 'y' && confirm != 'Y') {
                cout << "取消战斗。" << endl;
                Sleep(1200);
                return;
            }
        }

        auto selectedMonster = monsters[choice - 1];
        Battle battle(player, *selectedMonster);
        battle.start();

        // 战斗后检查怪物是否被击败
        if (selectedMonster->getHealthCur() <= 0) {
            system("cls");
            cout << selectedMonster->getName() << " 被击败了!" << endl;
            Sleep(1200);

            // 玩家获得奖励
            int moneyEarned = selectedMonster->dropMoney(rand() % 100); // 随机掉落绿宝石
            player.setMoney(player.getMoney() + moneyEarned);
            cout << player.getName() << " 获得了 " << moneyEarned << " 绿宝石!" << endl;
            Sleep(1200);

            // 从地图中移除被击败的怪物
            map.removeCreatureFromArea(map.getCurrentAreaId(), selectedMonster->getName());
        }
    }
    else if (choice != 0) {
        cout << "无效选择！" << endl;
        Sleep(1200);
    }
}


void Command::move() {
    auto connectedAreas = map.getConnectedAreas();
    if (connectedAreas.empty()) {
        cout << "没有可前往的区域！" << endl;
        Sleep(1200);
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
        system("cls");
        if (map.moveToConnectedArea(choice - 1)) {
            cout << "已移动到: " << map.getCurrentArea()->name << endl;
            map.displayCurrentPosition();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "\n按回车键继续...";
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        else {
            cout << "移动失败！" << endl;
            Sleep(1200);
        }
    }
    else if (choice != 0) {
        cout << "无效选择！" << endl;
        Sleep(1200);
    }
}

void Command::panel() {
    cout << "========== 玩家属性 ==========" << endl;
    cout << player.getName() << endl;
    player.showInfo();
    player.getWeapon().displayInfo();
    player.getArmor().displayInfo();

    cout << "技能:" << endl;
    for (const auto& skill : player.getSkill()) {
        skill->displayInfo();
        cout << "------------------------" << endl;
    }
    cout << "==============================" << endl;

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cout << "\n按回车键返回...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

void Command::showMap() const {
    map.displayMinimap();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cout << "\n按回车键返回...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

bool Command::isInBlacksmith() const {
    Area* currentArea = map.getCurrentArea();
    return currentArea && currentArea->type == BLACKSMITH;
}

bool Command::isInVillage() const {
    Area* currentArea = map.getCurrentArea();
    return currentArea && currentArea->type == VILLAGE;
}

void Command::serializePlayer(ofstream& out) {
    // 写入玩家基本信息
    string name = player.getName();
    size_t nameLength = name.size();
    out.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
    out.write(name.c_str(), nameLength);

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
    size_t weaponNameLength = weaponName.size();
    out.write(reinterpret_cast<const char*>(&weaponNameLength), sizeof(size_t));
    out.write(weaponName.c_str(), weaponNameLength);

    // 写入护甲信息
    string armorName = player.getArmor().getName();
    size_t armorNameLength = armorName.size();
    out.write(reinterpret_cast<const char*>(&armorNameLength), sizeof(size_t));
    out.write(armorName.c_str(), armorNameLength);

    // 写入技能信息
    int skillCount = static_cast<int>(player.getSkill().size());
    out.write(reinterpret_cast<const char*>(&skillCount), sizeof(int));
    for (const auto& skill : player.getSkill()) {
        string skillName = skill->getName();
        size_t skillNameLength = skillName.size();
        out.write(reinterpret_cast<const char*>(&skillNameLength), sizeof(size_t));
        out.write(skillName.c_str(), skillNameLength);
        int level = skill->getLevel();
        out.write(reinterpret_cast<const char*>(&level), sizeof(int));
    }

    // 写入增益状态
    TemporaryBuff buff = player.getTemporaryBuff();
    out.write(reinterpret_cast<const char*>(&buff.attack_bonus), sizeof(int));
    out.write(reinterpret_cast<const char*>(&buff.defense_bonus), sizeof(int));
    out.write(reinterpret_cast<const char*>(&buff.duration), sizeof(int));
}

void Command::serializeMap(ofstream& out) {
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

void Command::deserializePlayer(ifstream& in) {
    // 读取玩家基本信息
    size_t nameLength;
    in.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
    vector<char> nameBuffer(nameLength);
    in.read(nameBuffer.data(), nameLength);
    player.setName(string(nameBuffer.data(), nameLength));

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
    size_t weaponNameLength;
    in.read(reinterpret_cast<char*>(&weaponNameLength), sizeof(size_t));
    vector<char> weaponBuffer(weaponNameLength);
    in.read(weaponBuffer.data(), weaponNameLength);
    string weaponName(weaponBuffer.data(), weaponNameLength);

    // 根据装备名称设置装备
    if (weaponName == EquipmentTypes::WOODEN_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::WOODEN_SWORD);
    }
    else if (weaponName == EquipmentTypes::IRON_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::IRON_SWORD);
    }
    else if (weaponName == EquipmentTypes::DIAMOND_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::DIAMOND_SWORD);
    }

    // 读取护甲信息
    size_t armorNameLength;
    in.read(reinterpret_cast<char*>(&armorNameLength), sizeof(size_t));
    vector<char> armorBuffer(armorNameLength);
    in.read(armorBuffer.data(), armorNameLength);
    string armorName(armorBuffer.data(), armorNameLength);

    if (armorName == EquipmentTypes::LEATHER_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::LEATHER_ARMOR);
    }
    else if (armorName == EquipmentTypes::IRON_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::IRON_ARMOR);
    }
    else if (armorName == EquipmentTypes::DIAMOND_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::DIAMOND_ARMOR);
    }

    // 读取技能信息
    int skillCount = 0;
    in.read(reinterpret_cast<char*>(&skillCount), sizeof(int));

    player.clearSkills();
    for (int i = 0; i < skillCount; i++) {
        size_t skillNameLength;
        in.read(reinterpret_cast<char*>(&skillNameLength), sizeof(size_t));
        vector<char> skillBuffer(skillNameLength);
        in.read(skillBuffer.data(), skillNameLength);
        string skillName(skillBuffer.data(), skillNameLength);

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

void Command::deserializeMap(ifstream& in) {
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