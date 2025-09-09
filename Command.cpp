#include "Command.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// 新游戏命令实现
void NewGameCommand::execute() {
    // 清理旧数据
    if (player) delete player;
    if (currentMap) delete currentMap;
    if (currentBattle) delete currentBattle;

    // 初始化新游戏
    player = new Player(100, 100, 15, 5, 50, 50, 100, "勇者");
    currentMap = new Map(); // 使用简化的地图
    currentBattle = nullptr;

    // 给玩家初始装备
    player->addToInventory(new Equipment("铁剑", 5, 0));
    player->addToInventory(new Equipment("皮甲", 0, 3));

    cout << "新游戏初始化完成！你现在位于" << currentMap->getCurrentLocation().name << endl;
}

string NewGameCommand::getDescription() const override {
    return "新游戏开始";
}

// 保存游戏命令实现
void SaveGameCommand::execute() {
    if (!player) {
        cout << "无法保存：玩家不存在！" << endl;
        return;
    }

    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "保存失败：无法打开文件！" << endl;
        return;
    }

    // 保存玩家基本信息
    int hp = player->getHP();
    int maxHp = player->getMaxHP();
    int mp = player->getMP();
    int maxMp = player->getMaxMP();
    int atk = player->getATK();
    int def = player->getDEF();
    int gold = player->getGold();
    auto pos = player->getPosition();

    fout.write(reinterpret_cast<const char*>(&hp), sizeof(hp));
    fout.write(reinterpret_cast<const char*>(&maxHp), sizeof(maxHp));
    fout.write(reinterpret_cast<const char*>(&mp), sizeof(mp));
    fout.write(reinterpret_cast<const char*>(&maxMp), sizeof(maxMp));
    fout.write(reinterpret_cast<const char*>(&atk), sizeof(atk));
    fout.write(reinterpret_cast<const char*>(&def), sizeof(def));
    fout.write(reinterpret_cast<const char*>(&gold), sizeof(gold));
    fout.write(reinterpret_cast<const char*>(&pos.first), sizeof(pos.first));
    fout.write(reinterpret_cast<const char*>(&pos.second), sizeof(pos.second));

    cout << "游戏已保存到 " << filename << endl;
}

string SaveGameCommand::getDescription() const override {
    return "保存游戏到 " + filename;
}

// 加载游戏命令实现
void LoadGameCommand::execute() {
    // 清理当前玩家
    if (player) delete player;
    player = new Player(0, 0, 0, 0, 0, 0, 0, "勇者");

    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "加载失败：无法打开文件！" << endl;
        return;
    }

    // 加载玩家信息
    int hp, maxHp, mp, maxMp, atk, def, gold, x, y;
    fin.read(reinterpret_cast<char*>(&hp), sizeof(hp));
    fin.read(reinterpret_cast<char*>(&maxHp), sizeof(maxHp));
    fin.read(reinterpret_cast<char*>(&mp), sizeof(mp));
    fin.read(reinterpret_cast<char*>(&maxMp), sizeof(maxMp));
    fin.read(reinterpret_cast<char*>(&atk), sizeof(atk));
    fin.read(reinterpret_cast<char*>(&def), sizeof(def));
    fin.read(reinterpret_cast<char*>(&gold), sizeof(gold));
    fin.read(reinterpret_cast<char*>(&x), sizeof(x));
    fin.read(reinterpret_cast<char*>(&y), sizeof(y));

    // 恢复玩家状态
    player->setMaxHP(maxHp);
    player->setHP(hp);
    player->setMaxMP(maxMp);
    player->setMP(mp);
    player->setATK(atk);
    player->setDEF(def);
    player->setGold(gold);
    player->setPosition(x, y);

    cout << "游戏已从 " << filename << " 加载" << endl;
}

string SaveGameCommand::getDescription() const override {
    return "从 " + filename + " 加载游戏";
}

// 移动命令实现
void MoveCommand::execute() {
    if (!player || !map) {
        cout << "移动失败：玩家或地图不存在！" << endl;
        return;
    }

    // 保存当前位置用于撤销
    auto [x, y] = player->getPosition();
    prevX = x;
    prevY = y;

    // 执行移动
    if (map->move(player, direction)) {
        cout << "成功向" << direction << "移动！" << endl;

        // 移动后检查是否触发战斗
        if (map->checkEncounter(player)) {
            cout << "遭遇了怪物！战斗即将开始..." << endl;
        }
    }
    else {
        cout << "无法向" << direction << "移动！" << endl;
    }
}

void MoveCommand::undo() {
    if (!player || prevX == -1 || prevY == -1) return;

    player->setPosition(prevX, prevY);
    cout << "撤销移动，回到位置(" << prevX << "," << prevY << ")" << endl;
}

string MoveCommand::getDescription() const override {
    return "向" + direction + "移动";
}

// 面板显示命令实现
void PanelCommand::execute() {
    if (!player) {
        cout << "无法显示面板：玩家不存在！" << endl;
        return;
    }

    cout << "\n===== 玩家面板 =====" << endl;
    cout << "姓名：" << player->getName() << endl;
    cout << "生命值：" << player->getHP() << "/" << player->getMaxHP() << endl;
    cout << "魔法值：" << player->getMP() << "/" << player->getMaxMP() << endl;
    cout << "攻击力：" << player->getATK() << endl;
    cout << "防御力：" << player->getDEF() << endl;
    cout << "金币：" << player->getGold() << endl;

    auto [x, y] = player->getPosition();
    cout << "当前位置：(" << x << "," << y << ")" << endl;

    cout << "背包物品：";
    auto inventory = player->getInventory();
    if (inventory.empty()) {
        cout << "无" << endl;
    }
    else {
        for (auto item : inventory) {
            cout << item->getName() << " ";
        }
        cout << endl;
    }
    cout << "====================" << endl;
}

string PanelCommand::getDescription() const override {
    return "显示玩家面板";
}

// 交易命令实现
void TradeCommand::execute() {
    if (!player || !merchant || !merchant->isAlive()) {
        cout << "交易失败：交易对象不存在或已死亡！" << endl;
        return;
    }

    cout << "开始与" << merchant->getName() << "交易..." << endl;

    // 检查玩家是否有足够金币
    if (gold > 0 && player->getGold() < gold) {
        cout << "交易失败：金币不足！" << endl;
        return;
    }

    // 检查玩家是否有交易物品
    bool hasAllItems = true;
    for (auto item : items) {
        auto it = find(player->getInventory().begin(),
            player->getInventory().end(), item);
        if (it == player->getInventory().end()) {
            hasAllItems = false;
            break;
        }
    }

    if (!hasAllItems) {
        cout << "交易失败：缺少交易物品！" << endl;
        return;
    }

    // 执行交易
    player->setGold(player->getGold() - gold);
    for (auto item : items) {
        player->removeFromInventory(item);
    }

    // 这里可以添加获得的物品/奖励
    cout << "交易成功！" << endl;
}

string TradeCommand::getDescription() const override {
    return "与" + merchant->getName() + "交易";
}

// 恢复命令实现
void RecoverCommand::execute() {
    if (!player) {
        cout << "恢复失败：玩家不存在！" << endl;
        return;
    }

    // 保存当前状态用于撤销
    prevHealth = player->getHP();
    prevMana = player->getMP();

    // 执行恢复
    player->setHP(min(player->getHP() + health, player->getMaxHP()));
    player->setMP(min(player->getMP() + mana, player->getMaxMP()));

    cout << "恢复完成！当前状态："
        << player->getHP() << "/" << player->getMaxHP() << " HP, "
        << player->getMP() << "/" << player->getMaxMP() << " MP" << endl;
}

void RecoverCommand::undo() {
    if (!player || prevHealth == -1 || prevMana == -1) return;

    player->setHP(prevHealth);
    player->setMP(prevMana);
    cout << "撤销恢复效果" << endl;
}

string RecoverCommand::getDescription() const override {
    return "恢复 " + to_string(health) + " HP 和 " + to_string(mana) + " MP";
}

// 战斗选择命令实现
void BattleSelectionCommand::execute() {
    if (!battle || !player || monsters.empty() ||
        targetIndex < 0 || targetIndex >= monsters.size()) {
        cout << "选择失败：无效的战斗目标！" << endl;
        return;
    }

    // 设置战斗目标
    battle->setPlayer(player);
    battle->addMonsters(monsters);
    battle->setCurrentTarget(targetIndex);

    cout << "已选择战斗目标：" << monsters[targetIndex]->getName() << endl;
    cout << "战斗开始！" << endl;

    // 开始战斗循环
    battle->start();
}

string BattleSelectionCommand::getDescription() const override {
    return "选择战斗目标: " + (targetIndex >= 0 && targetIndex < monsters.size() ?
        monsters[targetIndex]->getName() : "无效目标");
}

// 命令管理器实现
CommandManager::~CommandManager() {
    for (auto cmd : commandHistory) {
        delete cmd;
    }
}

void CommandManager::executeCommand(Command* cmd) {
    if (!cmd) return;

    // 清除未来的命令（如果有）
    if (historyIndex < (int)commandHistory.size() - 1) {
        for (int i = commandHistory.size() - 1; i > historyIndex; --i) {
            delete commandHistory[i];
            commandHistory.pop_back();
        }
    }

    // 执行命令并添加到历史
    cmd->execute();
    commandHistory.push_back(cmd);
    historyIndex++;
}

bool CommandManager::undoLastCommand() {
    if (historyIndex >= 0) {
        commandHistory[historyIndex]->undo();
        historyIndex--;
        return true;
    }
    cout << "没有可撤销的命令！" << endl;
    return false;
}

bool CommandManager::redoLastCommand() {
    if (historyIndex < (int)commandHistory.size() - 1) {
        historyIndex++;
        commandHistory[historyIndex]->execute();
        return true;
    }
    cout << "没有可重做的命令！" << endl;
    return false;
}

void CommandManager::showHistory() const {
    cout << "\n===== 命令历史 =====" << endl;
    if (commandHistory.empty()) {
        cout << "无命令记录" << endl;
    }
    else {
        for (int i = 0; i < commandHistory.size(); ++i) {
            cout << (i == historyIndex ? "> " : "  ")
                << i + 1 << ". " << commandHistory[i]->getDescription() << endl;
        }
    }
    cout << "====================" << endl;
}
