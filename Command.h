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

// 命令基类 - 所有具体命令的抽象接口
// 采用命令模式设计，统一封装各种游戏操作
class Command {
public:
    virtual ~Command() = default;  // 虚析构函数，确保子类正确释放资源
    virtual void execute() = 0;    // 执行命令的纯虚函数
    virtual string getDescription() const = 0;  // 获取命令描述
};

// 新游戏命令 - 负责初始化新游戏状态
class NewGameCommand : public Command {
private:
    Player*& player;       // 引用外部玩家指针，允许修改玩家实例
    Map*& currentMap;      // 引用外部地图指针，允许替换地图实例
    Battle*& currentBattle;// 引用外部战斗指针，允许控制战斗状态

public:
    // 构造函数 - 接收玩家、地图和战斗的引用
    NewGameCommand(Player*& p, Map*& m, Battle*& b) : player(p), currentMap(m), currentBattle(b) {}

    void execute() override;
    string getDescription() const override;
};

// 保存游戏命令 - 负责将当前游戏状态保存到文件
class SaveGameCommand : public Command {
private:
    Player* player;        // 指向需要保存状态的玩家对象
    const string filename; // 保存文件的路径和名称

public:
    // 构造函数 - 接收玩家指针和保存文件名
    SaveGameCommand(Player* p, const std::string& fn) : player(p), filename(fn) {}

    void execute() override;
    string getDescription() const override;
};

// 加载游戏命令 - 负责从文件恢复游戏状态
class LoadGameCommand : public Command {
private:
    Player*& player;       // 引用外部玩家指针，用于替换为加载的玩家
    Map*& currentMap;      // 引用外部地图指针，用于更新地图状态
    const string filename; // 加载文件的路径和名称

public:
    // 构造函数 - 接收玩家引用、地图引用和加载文件名
    LoadGameCommand(Player*& p, Map*& m, const string& fn) : player(p), currentMap(m), filename(fn) {}

    void execute() override;
    string getDescription() const override;
};

// 移动命令 - 负责处理玩家在地图上的移动
class MoveCommand : public Command {
private:
    Player* player;        // 指向需要移动的玩家
    Map* map;              // 指向玩家所在的地图
    const string direction;// 移动方向（如"上"、"下"、"左"、"右"）

public:
    // 构造函数 - 接收玩家、地图和移动方向
    MoveCommand(Player* p, Map* m, const string& dir) : player(p), map(m), direction(dir) {}

    void execute() override; 
    string getDescription() const override; 
};

// 面板显示命令 - 负责展示玩家状态信息
class PanelCommand : public Command {
private:
    Player* player;        // 指向需要显示信息的玩家

public:
    // 构造函数 - 接收玩家指针
    PanelCommand(Player* p) : player(p) {}

    void execute() override;
    string getDescription() const override;
};

// 交易命令 - 负责处理玩家与NPC/怪物的交易逻辑
class TradeCommand : public Command {
private:
    Player* player;                // 指向进行交易的玩家
    Monster* merchant;             // 指向交易对象（商人或可交易怪物）
    vector<Equipment*> items;      // 交易所需的物品列表
    int money;                     // 交易所需的金钱数量

public:
    // 构造函数 - 接收玩家、交易对象、物品列表和金钱数量
    TradeCommand(Player* p, Monster* m, const vector<Equipment*>& i, int mon) :
        player(p), merchant(m), items(i), money(mon) {
    }

    void execute() override;
    string getDescription() const override;
};

// 恢复命令 - 负责恢复玩家的生命值和魔法值
class RecoverCommand : public Command {
private:
    Player* player;        // 指向需要恢复状态的玩家
    int health;            // 要恢复的生命值
    int mana;              // 要恢复的魔法值

public:
    // 构造函数 - 接收玩家指针和恢复数值
    RecoverCommand(Player* p, int h, int m) :
        player(p), health(h), mana(m) {
    }

    void execute() override;
    string getDescription() const override;
};

// 战斗选择命令 - 负责处理战斗目标选择和战斗初始化
class BattleSelectionCommand : public Command {
private:
    Battle* battle;                // 指向战斗实例
    Player* player;                // 指向参战玩家
    vector<Monster*> monsters;     // 参战怪物列表
    int targetIndex;               // 选中的目标索引

public:
    // 构造函数 - 接收战斗实例、玩家、怪物列表和目标索引
    BattleSelectionCommand(Battle* b, Player* p, const vector<Monster*>& m, int idx) :
        battle(b), player(p), monsters(m), targetIndex(idx) {
    }

    void execute() override;
    string getDescription() const override;  // 返回命令描述
};

// 命令管理器 - 负责命令的执行和历史记录管理
class CommandManager {
private:
    vector<Command*> commandHistory;  // 存储已执行的命令历史

public:
    CommandManager() {}  // 默认构造函数
    ~CommandManager();   // 析构函数，负责释放命令对象

    void executeCommand(Command* cmd); 
    void showHistory() const;           // 显示命令执行历史
};

#endif // COMMAND_H
