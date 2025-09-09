#include "Command.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

// 新游戏命令实现
void NewGameCommand::execute() {
    // 清理旧数据：在创建新游戏前，必须释放之前的玩家、地图和战斗对象
    // 防止内存泄漏，确保新游戏状态不受旧数据影响
    if (player) delete player;
    if (currentMap) delete currentMap;
    if (currentBattle) delete currentBattle;

    // 初始化新玩家
    // 参数顺序：角色名称、生命上限、当前生命、攻击力、防御力、魔法上限、当前魔法、初始金钱
    player = new Player("勇者", 100, 20, 2, 0, 50, 5, 100);
    // 创建新地图（地图内部会初始化初始位置和场景数据）
    currentMap = new Map();
    // 新游戏初始状态下无战斗，将战斗指针置空
    currentBattle = nullptr;

    // 提示玩家新游戏已准备就绪，并显示初始位置
    cout << "新游戏初始化完成！你现在位于" << currentMap->getCurrentLocation().name << endl;
}

string NewGameCommand::getDescription() const override {
    return "新游戏开始";
}

// 保存游戏命令实现
void SaveGameCommand::execute() {
    // 合法性检查：如果玩家对象不存在，无法执行保存操作
    if (!player) {
        cout << "无法保存：玩家不存在！" << endl;
        return;
    }

    // 以二进制模式打开文件（二进制模式适合存储数值型数据，避免文本模式的格式转换问题）
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "保存失败：无法打开文件！" << endl;
        return;
    }

    // 读取玩家核心属性：这些属性共同构成了玩家的当前状态
    int health_cur = player->getHealthCur();       // 当前生命值
    int health_max = player->getHealthMax();       // 生命上限
    int magic_power_cur = player->getMagicPowerCur(); // 当前魔法值
    int magic_power_max = player->getMagicPowerMax(); // 魔法上限
    int attack = player->getAttack();              // 攻击力
    int defense = player->getDefense();            // 防御力
    int money = player->getMoney();                // 持有金钱
    auto pos = player->getPosition();              // 当前坐标（以pair形式存储）

    // 按固定顺序写入文件：必须与加载时的读取顺序完全一致
    // 使用reinterpret_cast进行类型转换，将整数指针转为字符指针以符合write函数要求
    fout.write(reinterpret_cast<const char*>(&health_cur), sizeof(health_cur));
    fout.write(reinterpret_cast<const char*>(&health_max), sizeof(health_max));
    fout.write(reinterpret_cast<const char*>(&magic_power_cur), sizeof(magic_power_cur));
    fout.write(reinterpret_cast<const char*>(&magic_power_max), sizeof(magic_power_max));
    fout.write(reinterpret_cast<const char*>(&attack), sizeof(attack));
    fout.write(reinterpret_cast<const char*>(&defense), sizeof(defense));
    fout.write(reinterpret_cast<const char*>(&money), sizeof(money));
    fout.write(reinterpret_cast<const char*>(&pos.first), sizeof(pos.first));  // X坐标
    fout.write(reinterpret_cast<const char*>(&pos.second), sizeof(pos.second));// Y坐标

    // 保存完成后关闭文件流
    fout.close();
    cout << "游戏已保存到 " << filename << endl;
}

string SaveGameCommand::getDescription() const override {
    return "保存游戏到 " + filename;
}

// 加载游戏命令实现
void LoadGameCommand::execute() {
    // 清理现有玩家对象：加载前先释放当前玩家，避免内存泄漏
    if (player) delete player;
    // 创建临时玩家对象，用于接收加载的数据
    player = new Player("", 0, 0, 0, 0, 0, 0, 0);

    // 以二进制读模式打开文件
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "加载失败：无法打开文件！" << endl;
        return;
    }

    // 定义变量存储读取的属性：顺序必须与保存时完全一致
    int health_cur, health_max, magic_power_cur, magic_power_max, attack, defense, money, x, y;
    fin.read(reinterpret_cast<char*>(&health_cur), sizeof(health_cur));
    fin.read(reinterpret_cast<char*>(&health_max), sizeof(health_max));
    fin.read(reinterpret_cast<char*>(&magic_power_cur), sizeof(magic_power_cur));
    fin.read(reinterpret_cast<char*>(&magic_power_max), sizeof(magic_power_max));
    fin.read(reinterpret_cast<char*>(&attack), sizeof(attack));
    fin.read(reinterpret_cast<char*>(&defense), sizeof(defense));
    fin.read(reinterpret_cast<char*>(&money), sizeof(money));
    fin.read(reinterpret_cast<char*>(&x), sizeof(x));  // X坐标
    fin.read(reinterpret_cast<char*>(&y), sizeof(y));  // Y坐标

    // 关闭文件流
    fin.close();

    // 恢复玩家状态：先设置上限值，再设置当前值，避免当前值超过上限
    player->setHealthMax(health_max);
    player->setHealthCur(health_cur);
    player->setMagicPowerMax(magic_power_max);
    player->setMagicPowerCur(magic_power_cur);
    player->setAttack(attack);
    player->setDefense(defense);
    player->setMoney(money);
    player->setPosition(x, y);  // 恢复玩家在地图上的位置

    cout << "游戏已从 " << filename << " 加载" << endl;
}

string LoadGameCommand::getDescription() const override {
    return "从 " + filename + " 加载游戏";
}

// 移动命令实现
void MoveCommand::execute() {
    // 合法性检查：玩家或地图不存在时无法移动
    if (!player || !map) {
        cout << "移动失败：玩家或地图不存在！" << endl;
        return;
    }

    // 调用地图的移动方法：地图内部会判断移动是否合法（如是否超出边界、是否有障碍物）
    if (map->move(direction)) {
        // 移动成功：更新玩家位置并提示
        cout << "成功向" << direction << "移动！" << endl;

        // 移动后触发遇敌检测：地图根据当前位置的遇敌概率决定是否触发战斗
        if (map->checkEncounter()) {
            cout << "遭遇了怪物！战斗即将开始..." << endl;
        }
    }
    else {
        // 移动失败：可能是边界或障碍物阻挡
        cout << "无法向" << direction << "移动！" << endl;
    }
}

string MoveCommand::getDescription() const override {
    return "向" + direction + "移动";
}

// 面板显示命令实现
void PanelCommand::execute() {
    // 合法性检查：玩家不存在时无法显示面板
    if (!player) {
        cout << "无法显示面板：玩家不存在！" << endl;
        return;
    }

    // 显示玩家详细信息面板
    cout << "\n===== 玩家面板 =====" << endl;
    cout << "姓名：" << player->getName() << endl;
    cout << "生命值：" << player->getHealthCur() << "/" << player->getHealthMax() << endl;
    cout << "魔法值：" << player->getMagicPowerCur() << "/" << player->getMagicPowerMax() << endl;
    cout << "攻击力：" << player->getAttack() << endl;
    cout << "防御力：" << player->getDefense() << endl;
    cout << "金钱：" << player->getMoney() << endl;

    // 显示当前坐标位置
    auto [x, y] = player->getPosition();
    cout << "当前位置：(" << x << "," << y << ")" << endl;

    // 显示背包物品列表
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
    // 合法性检查：交易对象不存在或已死亡时无法交易
    if (!player || !merchant || !merchant->isAlive()) {
        cout << "交易失败：交易对象不存在或已死亡！" << endl;
        return;
    }

    cout << "开始与" << merchant->getName() << "交易..." << endl;

    // 金钱充足性检查：仅当需要支付金钱且玩家金钱不足时交易失败
    if (money > 0 && player->getMoney() < money) {
        cout << "交易失败：金钱不足！" << endl;
        return;
    }

    // 检查是否拥有所有必要交易物品
    bool hasAllItems = true;
    for (auto item : items) {
        // 在玩家背包中查找所需物品
        auto it = find(player->getInventory().begin(), player->getInventory().end(), item);
        if (it == player->getInventory().end()) {
            hasAllItems = false;
            break;
        }
    }
    if (!hasAllItems) {
        cout << "交易失败：缺少交易物品！" << endl;
        return;
    }

    // 执行交易扣减：扣除相应金钱和物品
    player->setMoney(player->getMoney() - money);
    for (auto item : items) {
        player->removeFromInventory(item);
    }

    // （交易奖励逻辑可在此处添加，如添加新物品到玩家背包）
    cout << "交易成功！" << endl;
}

string TradeCommand::getDescription() const override {
    return "与" + merchant->getName() + "交易";
}

// 恢复命令实现
void RecoverCommand::execute() {
    // 合法性检查：玩家不存在时无法执行恢复
    if (!player) {
        cout << "恢复失败：玩家不存在！" << endl;
        return;
    }

    // 计算恢复后的值：使用min函数确保恢复后的值不超过上限
    int newHealth = min(player->getHealthCur() + health, player->getHealthMax());
    int newMana = min(player->getMagicPowerCur() + mana, player->getMagicPowerMax());

    // 应用恢复效果
    player->setHealthCur(newHealth);
    player->setMagicPowerCur(newMana);

    // 显示恢复后的状态
    cout << "恢复完成！当前状态："
        << player->getHealthCur() << "/" << player->getHealthMax() << " 生命值, "
        << player->getMagicPowerCur() << "/" << player->getMagicPowerMax() << " 魔法值" << endl;
}

string RecoverCommand::getDescription() const override {
    return "恢复 " + to_string(health) + " 生命值 和 " + to_string(mana) + " 魔法值";
}

// 战斗选择命令实现
void BattleSelectionCommand::execute() {
    // 验证战斗参数合法性：检查战斗环境、玩家、怪物列表和目标索引是否有效
    if (!battle || !player || monsters.empty() ||
        targetIndex < 0 || targetIndex >= monsters.size()) {
        cout << "选择失败：无效的战斗目标！" << endl;
        return;
    }

    // 初始化战斗环境：设置参战者和当前目标
    battle->setPlayer(player);
    battle->addMonsters(monsters);
    battle->setCurrentTarget(targetIndex);

    // 提示战斗开始
    cout << "已选择战斗目标：" << monsters[targetIndex]->getName() << endl;
    cout << "战斗开始！" << endl;
    battle->start();  // 启动战斗流程
}

string BattleSelectionCommand::getDescription() const override {
    return "选择战斗目标: " + (targetIndex >= 0 && targetIndex < monsters.size() ?
        monsters[targetIndex]->getName() : "无效目标");
}

// 命令管理器实现
CommandManager::~CommandManager() {
    // 释放所有命令对象：在管理器销毁时，必须释放所有已执行命令的内存
    // 防止内存泄漏，每个命令都是通过new创建的
    for (auto cmd : commandHistory) {
        delete cmd;
    }
}

void CommandManager::executeCommand(Command* cmd) {
    if (!cmd) return;  // 空命令不执行

    // 执行命令并将其加入历史记录
    cmd->execute();
    commandHistory.push_back(cmd);
}

void CommandManager::showHistory() const {
    // 显示所有已执行的命令历史
    cout << "\n===== 命令历史 =====" << endl;
    if (commandHistory.empty()) {
        cout << "无命令记录" << endl;
    }
    else {
        for (int i = 0; i < commandHistory.size(); ++i) {
            cout << i + 1 << ". " << commandHistory[i]->getDescription() << endl;
        }
    }
    cout << "====================" << endl;
}
