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

// 命令基类
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
    virtual string getDescription() const = 0;
    virtual void undo() {} // 可选的撤销功能
};

// 新游戏命令
class NewGameCommand : public Command {
private:
    Player*& player;       // 引用玩家指针，允许修改外部玩家
    Map*& currentMap;      // 引用地图指针
    Battle*& currentBattle;// 引用战斗指针

public:
    NewGameCommand(Player*& p, Map*& m, Battle*& b): player(p), currentMap(m), currentBattle(b) {}

    void execute() override;
    string getDescription() const override;
};

// 保存游戏命令
class SaveGameCommand : public Command {
private:
    Player* player;
    const string filename;

public:
    SaveGameCommand(Player* p, const std::string& fn): player(p), filename(fn) {}

    void execute() override;
    string getDescription() const override;

// 加载游戏命令
class LoadGameCommand : public Command {
private:
    Player*& player;       // 引用玩家指针
    Map*& currentMap;      // 引用地图指针
    const string filename;

public:
    LoadGameCommand(Player*& p, Map*& m, const string& fn): player(p), currentMap(m), filename(fn) {}

    void execute() override;
    string getDescription() const override;
};

// 移动命令
class MoveCommand : public Command {
private:
    Player* player;
    Map* map;
    const string direction;
    int prevX, prevY;      // 用于撤销

public:
    MoveCommand(Player* p, Map* m, const string& dir): player(p), map(m), direction(dir), prevX(-1), prevY(-1) {}

    void execute() override;
    void undo() override;
    string getDescription() const override;
};

// 面板显示命令
class PanelCommand : public Command {
private:
    Player* player;

public:
    PanelCommand(Player* p) : player(p) {}

    void execute() override;
    string getDescription() const override;

// 交易命令
class TradeCommand : public Command {
private:
    Player* player;
    Monster* merchant;     // 可交易的怪物/NPC
    vector<Equipment*> items;
    int gold;

public:
    TradeCommand(Player* p, Monster* m, const vector<Equipment*>& i, int g): player(p), merchant(m), items(i), gold(g) {}

    void execute() override;
    string getDescription() const override;
};

// 恢复命令
class RecoverCommand : public Command {
private:
    Player* player;
    int health;
    int mana;
    int prevHealth, prevMana; // 用于撤销

public:
    RecoverCommand(Player* p, int h, int m): player(p), health(h), mana(m), prevHealth(-1), prevMana(-1) {}

    void execute() override;
    void undo() override;
    string getDescription() const override;
};

// 战斗选择命令
class BattleSelectionCommand : public Command {
private:
    Battle* battle;
    Player* player;
    vector<Monster*> monsters;
    int targetIndex;

public:
    BattleSelectionCommand(Battle* b, Player* p, const vector<Monster*>& m, int idx): battle(b), player(p), monsters(m), targetIndex(idx) {}

    void execute() override;
    string getDescription() const override;
};

// 命令管理器
class CommandManager {
private:
    vector<Command*> commandHistory;
    int historyIndex;

public:
    CommandManager() : historyIndex(-1) {}
    ~CommandManager();

    void executeCommand(Command* cmd);
    bool undoLastCommand();
    bool redoLastCommand();
    void showHistory() const;
};

#endif // COMMAND_H
