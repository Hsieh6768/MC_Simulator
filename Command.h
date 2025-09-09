#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include "Equipment.h"
#include "Battle.h"

using namespace std;

// 命令基类：抽象接口，统一所有命令的执行与描述
class Command {
public:
    virtual ~Command() = default;  // 虚析构：确保子类资源正常释放
    virtual void execute() = 0;    // 纯虚函数：执行命令逻辑
    virtual string getDescription() const = 0;  // 纯虚函数：获取命令描述
};

// 新游戏命令：初始化新游戏的玩家、地图、战斗状态
class NewGameCommand : public Command {
private:
    Player*& player;       // 引用玩家指针：修改外部玩家实例
    Map*& currentMap;      // 引用地图指针：替换外部地图实例
    Battle*& currentBattle;// 引用战斗指针：控制外部战斗状态

public:
    // 构造：接收玩家、地图、战斗的引用
    NewGameCommand(Player*& p, Map*& m, Battle*& b) : player(p), currentMap(m), currentBattle(b) {}
    void execute() override;
    string getDescription() const override;
};

// 保存游戏命令：将当前玩家状态写入文件
class SaveGameCommand : public Command {
private:
    Player* player;        // 指向需保存状态的玩家
    const string filename; // 保存文件的路径+名称

public:
    // 构造：接收玩家指针和保存文件名
    SaveGameCommand(Player* p, const std::string& fn) : player(p), filename(fn) {}
    void execute() override;
    string getDescription() const override;
};

// 加载游戏命令：从文件恢复玩家与地图状态
class LoadGameCommand : public Command {
private:
    Player*& player;       // 引用玩家指针：替换为加载的玩家
    Map*& currentMap;      // 引用地图指针：更新地图状态
    const string filename; // 加载文件的路径+名称

public:
    // 构造：接收玩家引用、地图引用和加载文件名
    LoadGameCommand(Player*& p, Map*& m, const string& fn) : player(p), currentMap(m), filename(fn) {}
    void execute() override;
    string getDescription() const override;
};

// 移动命令：适配新地图，支持区域编号/方向移动
class MoveCommand : public Command {
private:
    Player* player;        // 指向需移动的玩家
    Map* map;              // 指向新地图（需支持区域连接逻辑）
    const string direction;// 移动参数

public:
    // 构造：接收玩家、地图和移动参数
    MoveCommand(Player* p, Map* m, const string& dir) : player(p), map(m), direction(dir) {}
    void execute() override;
    string getDescription() const override;
};

// 面板显示命令：展示玩家信息+当前地图区域信息
class PanelCommand : public Command {
private:
    Player* player;        // 指向需展示信息的玩家
    Map* map;              // 指向地图：获取当前区域信息

public:
    // 构造：接收玩家和地图指针
    PanelCommand(Player* p, Map* m) : player(p), map(m) {}
    void execute() override;
    string getDescription() const override;
};

// 交易命令：处理玩家与NPC/商人的物品+金钱交易
class TradeCommand : public Command {
private:
    Player* player;        // 指向进行交易的玩家
    Monster* merchant;     // 指向交易对象（商人/NPC）
    vector<Equipment*> items; // 交易所需物品列表
    int money;             // 交易所需金钱数量

public:
    // 构造：接收玩家、商人、物品列表和金钱
    TradeCommand(Player* p, Monster* m, const vector<Equipment*>& i, int mon) :
        player(p), merchant(m), items(i), money(mon) {
    }
    void execute() override;
    string getDescription() const override;
};

// 恢复命令：恢复玩家指定数值的生命值和魔法值
class RecoverCommand : public Command {
private:
    Player* player;        // 指向需恢复状态的玩家
    int health;            // 恢复的生命值
    int mana;              // 恢复的魔法值

public:
    // 构造：接收玩家指针和恢复数值
    RecoverCommand(Player* p, int h, int m) :player(p), health(h), mana(m) {}
    void execute() override;
    string getDescription() const override;
};

// 战斗选择命令：选择战斗目标并初始化战斗
class BattleSelectionCommand : public Command {
private:
    Battle* battle;        // 指向战斗实例
    Player* player;        // 指向参战玩家
    vector<Monster*> monsters; // 参战怪物列表
    int targetIndex;       // 选中的怪物目标索引

public:
    // 构造：接收战斗、玩家、怪物列表和目标索引
    BattleSelectionCommand(Battle* b, Player* p, const vector<Monster*>& m, int idx) :battle(b), player(p), monsters(m), targetIndex(idx) {}
    void execute() override;
    string getDescription() const override;
};

// 命令管理器：执行命令+管理命令历史
class CommandManager {
private:
    vector<Command*> commandHistory; // 存储已执行的命令历史

public:
    CommandManager() {}  // 默认构造
    ~CommandManager();   // 析构：释放所有命令资源
    void executeCommand(Command* cmd); // 执行命令并加入历史
    void showHistory() const;          // 显示所有命令历史
};

#endif // COMMAND_H
