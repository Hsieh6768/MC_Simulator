#include "Command.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

// 新游戏命令：初始化新游戏状态（清理旧数据+创建玩家/地图）
void NewGameCommand::execute() {
    // 清理旧资源：避免内存泄漏，确保新游戏状态纯净
    if (player) delete player;
    if (currentMap) delete currentMap;
    if (currentBattle) delete currentBattle;

    // 初始化玩家
    player = new Player("勇者", 100, 20, 2, 0, 50, 5, 100);
    currentMap = new Map(); // 初始化新地图
    currentBattle = nullptr; // 新游戏初始无战斗

    // 绑定玩家到地图初始区域：通过地图接口获取初始区域ID，设置玩家位置
    player->setPosition(currentMap->getInitialAreaId(), 0);
    cout << "新游戏初始化完成！你现在位于" << currentMap->getCurrentAreaName() << endl;
}

string NewGameCommand::getDescription() const {
    return "新游戏开始";
}

// 保存游戏命令：将玩家状态（含当前区域）写入二进制文件
void SaveGameCommand::execute() {
    // 合法性校验：无玩家则无法保存
    if (!player) {
        cout << "无法保存：玩家不存在！" << endl;
        return;
    }

    // 二进制模式打开文件：适合存储数值型数据，避免文本格式转换误差
    ofstream fout(filename, ios::binary);
    if (!fout) {
        cout << "保存失败：无法打开文件！" << endl;
        return;
    }

    // 读取玩家核心状态（基础属性+当前区域ID）
    int health_cur = player->getHealthCur();       // 当前生命值
    int health_max = player->getHealthMax();       // 生命上限
    int magic_power_cur = player->getMagicPowerCur(); // 当前魔法值
    int magic_power_max = player->getMagicPowerMax(); // 魔法上限
    int attack = player->getAttack();              // 攻击力
    int defense = player->getDefense();            // 防御力
    int money = player->getMoney();                // 持有金钱
    int currentAreaId = player->getPosition().first; // 当前所在区域ID

    // 按固定顺序写入文件：需与加载时读取顺序完全一致
    fout.write(reinterpret_cast<const char*>(&health_cur), sizeof(health_cur));
    fout.write(reinterpret_cast<const char*>(&health_max), sizeof(health_max));
    fout.write(reinterpret_cast<const char*>(&magic_power_cur), sizeof(magic_power_cur));
    fout.write(reinterpret_cast<const char*>(&magic_power_max), sizeof(magic_power_max));
    fout.write(reinterpret_cast<const char*>(&attack), sizeof(attack));
    fout.write(reinterpret_cast<const char*>(&defense), sizeof(defense));
    fout.write(reinterpret_cast<const char*>(&money), sizeof(money));
    fout.write(reinterpret_cast<const char*>(&currentAreaId), sizeof(currentAreaId));

    fout.close(); // 关闭文件流，确保数据写入完成
    cout << "游戏已保存到 " << filename << endl;
}

string SaveGameCommand::getDescription() const {
    return "保存游戏到 " + filename;
}

// 加载游戏命令：从二进制文件恢复玩家与地图状态
void LoadGameCommand::execute() {
    // 清理当前玩家：避免内存泄漏，为加载数据腾出空间
    if (player) delete player;
    player = new Player("", 0, 0, 0, 0, 0, 0, 0); // 创建空玩家对象

    // 二进制模式打开文件：与保存模式对应
    ifstream fin(filename, ios::binary);
    if (!fin) {
        cout << "加载失败：无法打开文件！" << endl;
        return;
    }

    // 定义变量存储加载的状态（顺序与保存时完全一致）
    int health_cur, health_max, magic_power_cur, magic_power_max, attack, defense, money;
    int currentAreaId; // 加载的目标区域ID

    // 读取文件数据到变量
    fin.read(reinterpret_cast<char*>(&health_cur), sizeof(health_cur));
    fin.read(reinterpret_cast<char*>(&health_max), sizeof(health_max));
    fin.read(reinterpret_cast<char*>(&magic_power_cur), sizeof(magic_power_cur));
    fin.read(reinterpret_cast<char*>(&magic_power_max), sizeof(magic_power_max));
    fin.read(reinterpret_cast<char*>(&attack), sizeof(attack));
    fin.read(reinterpret_cast<char*>(&defense), sizeof(defense));
    fin.read(reinterpret_cast<char*>(&money), sizeof(money));
    fin.read(reinterpret_cast<char*>(&currentAreaId), sizeof(currentAreaId));

    fin.close(); // 关闭文件流

    // 恢复玩家状态：先设上限再设当前值，避免当前值超出上限
    player->setHealthMax(health_max);
    player->setHealthCur(health_cur);
    player->setMagicPowerMax(magic_power_max);
    player->setMagicPowerCur(magic_power_cur);
    player->setAttack(attack);
    player->setDefense(defense);
    player->setMoney(money);
    player->setPosition(currentAreaId, 0); // 恢复玩家到加载的区域

    // 同步地图状态：将地图切换到玩家加载的区域
    if (currentMap) {
        currentMap->switchToArea(currentAreaId);
    }

    cout << "游戏已从 " << filename << " 加载" << endl;
}

string LoadGameCommand::getDescription() const {
    return "从 " + filename + " 加载游戏";
}

// 移动命令：适配新地图的区域移动（按编号选择目标区域）
void MoveCommand::execute() {
    // 合法性校验：无玩家或地图则无法移动
    if (!player || !map) {
        cout << "移动失败：玩家或地图不存在！" << endl;
        return;
    }

    try {
        // 转换输入：用户输入1-based编号，转为地图需要的0-based索引
        int targetAreaIdx = stoi(direction) - 1;

        // 检查区域可达性：调用地图接口判断目标区域是否可移动
        if (map->isAreaReachable(targetAreaIdx)) {
            // 执行移动：获取目标区域ID，更新玩家位置
            int targetAreaId = map->moveToArea(targetAreaIdx);
            player->setPosition(targetAreaId, 0);

            // 显示移动结果：输出新区域名称与描述
            cout << "成功移动到【" << map->getCurrentAreaName() << "】" << endl;
            cout << "区域描述：" << map->getCurrentAreaDesc() << endl;

            // 触发遇敌检测：若当前区域有怪物，提示战斗
            if (map->hasMonsterInCurrentArea()) {
                cout << "遭遇了怪物！战斗即将开始..." << endl;
            }
        }
        else {
            // 移动失败：提示并显示可到达的区域列表
            cout << "无法移动到该区域！请选择可到达的区域编号" << endl;
            map->showReachableAreas();
        }
    }
    catch (invalid_argument&) {
        // 输入异常：用户输入非数字，提示正确格式
        cout << "无效输入！新地图需输入区域编号（如1、2、3）" << endl;
        map->showReachableAreas();
    }
}

string MoveCommand::getDescription() const {
    return "移动到区域（编号：" + direction + "）";
}

// 面板命令：显示玩家属性+当前地图区域信息
void PanelCommand::execute() {
    // 合法性校验：无玩家则无法显示面板
    if (!player) {
        cout << "无法显示面板：玩家不存在！" << endl;
        return;
    }

    // 输出玩家核心属性面板
    cout << "\n===== 玩家面板 =====" << endl;
    cout << "姓名：" << player->getName() << endl;
    cout << "生命值：" << player->getHealthCur() << "/" << player->getHealthMax() << endl;
    cout << "魔法值：" << player->getMagicPowerCur() << "/" << player->getMagicPowerMax() << endl;
    cout << "攻击力：" << player->getAttack() << endl;
    cout << "防御力：" << player->getDefense() << endl;
    cout << "金钱：" << player->getMoney() << endl;

    // 输出当前地图区域信息（若地图存在）
    if (map) {
        cout << "当前区域：" << map->getCurrentAreaName() << "（ID：" << player->getPosition().first << "）" << endl;
    }

    // 输出背包物品列表
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

string PanelCommand::getDescription() const {
    return "显示玩家面板（含当前区域信息）";
}

// 交易命令：处理玩家与商人的物品+金钱交换
void TradeCommand::execute() {
    // 合法性校验：玩家/商人不存在，或商人已死亡则无法交易
    if (!player || !merchant || !merchant->isAlive()) {
        cout << "交易失败：交易对象不存在或已死亡！" << endl;
        return;
    }

    cout << "开始与" << merchant->getName() << "交易..." << endl;

    // 金钱校验：若需支付金钱且玩家余额不足，交易失败
    if (money > 0 && player->getMoney() < money) {
        cout << "交易失败：金钱不足！" << endl;
        return;
    }

    // 物品校验：检查玩家是否拥有所有交易所需物品
    bool hasAllItems = true;
    for (auto item : items) {
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

    // 执行交易扣减：扣除玩家对应金钱与物品
    player->setMoney(player->getMoney() - money);
    for (auto item : items) {
        player->removeFromInventory(item);
    }

    cout << "交易成功！" << endl;
}

string TradeCommand::getDescription() const {
    return "与" + merchant->getName() + "交易";
}

// 恢复命令：恢复玩家指定数值的生命值与魔法值
void RecoverCommand::execute() {
    // 合法性校验：无玩家则无法执行恢复
    if (!player) {
        cout << "恢复失败：玩家不存在！" << endl;
        return;
    }

    // 计算恢复后的值：用min确保不超过属性上限
    int newHealth = min(player->getHealthCur() + health, player->getHealthMax());
    int newMana = min(player->getMagicPowerCur() + mana, player->getMagicPowerMax());

    // 应用恢复效果
    player->setHealthCur(newHealth);
    player->setMagicPowerCur(newMana);

    // 输出恢复结果
    cout << "恢复完成！当前状态："
        << player->getHealthCur() << "/" << player->getHealthMax() << " 生命值, "
        << player->getMagicPowerCur() << "/" << player->getMagicPowerMax() << " 魔法值" << endl;
}

string RecoverCommand::getDescription() const {
    return "恢复 " + to_string(health) + " 生命值 和 " + to_string(mana) + " 魔法值";
}

// 战斗选择命令：选择目标怪物并初始化战斗
void BattleSelectionCommand::execute() {
    // 合法性校验：战斗实例/玩家不存在、怪物列表空、目标索引无效，均无法选择
    if (!battle || !player || monsters.empty() || targetIndex < 0 || targetIndex >= monsters.size()) {
        cout << "选择失败：无效的战斗目标！" << endl;
        return;
    }

    // 初始化战斗参数：设置参战玩家、怪物列表、当前目标
    battle->setPlayer(player);
    battle->addMonsters(monsters);
    battle->setCurrentTarget(targetIndex);

    // 输出战斗开始提示
    cout << "已选择战斗目标：" << monsters[targetIndex]->getName() << endl;
    cout << "战斗开始！" << endl;
    battle->start(); // 启动战斗流程
}

string BattleSelectionCommand::getDescription() const {
    // 拼接目标名称（无效索引时显示"无效目标"）
    return "选择战斗目标: " + (targetIndex >= 0 && targetIndex < monsters.size() ?
        monsters[targetIndex]->getName() : "无效目标");
}

// 命令管理器析构函数：释放所有命令对象，避免内存泄漏
CommandManager::~CommandManager() {
    // 遍历命令历史列表，逐个删除命令实例
    for (auto cmd : commandHistory) {
        delete cmd;
    }
    // 清空列表（可选，析构后列表会自动销毁）
    commandHistory.clear();
}

// 命令管理器：执行命令并加入历史记录
void CommandManager::executeCommand(Command* cmd) {
    // 空命令校验：避免执行空指针
    if (!cmd) {
        cout << "执行失败：无效命令！" << endl;
        return;
    }

    cmd->execute(); // 执行命令逻辑
    commandHistory.push_back(cmd); // 将命令加入历史记录
}

// 命令管理器：显示所有已执行的命令历史
void CommandManager::showHistory() const {
    cout << "\n===== 命令历史 =====" << endl;
    // 无历史记录时提示
    if (commandHistory.empty()) {
        cout << "暂无命令记录" << endl;
    }
    else {
        // 遍历历史列表，按序号输出命令描述
        for (size_t i = 0; i < commandHistory.size(); ++i) {
            cout << i + 1 << ". " << commandHistory[i]->getDescription() << endl;
        }
    }
    cout << "====================" << endl;
}
