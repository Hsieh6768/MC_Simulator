#ifndef COMMAND_H
#define COMMAND_H

#include "Player.h"
#include "Map.h"
#include "Battle.h"
#include <string>
#include <fstream>
#include <vector>

class Command {
public:
    Command(Player& player, Map& map);

    // 主要命令函数
    void NewGame();                    // 创建新游戏
    bool SaveGame(const std::string& filename); // 保存游戏
    bool LoadGame(const std::string& filename); // 加载游戏
    void Trade();                      // 装备交易与升级
    void Recover();                    // 恢复玩家状态
    void BattleSelection();            // 选择战斗目标
    void Move();                       // 移动至其他区域
    void Panel();                      // 显示玩家属性面板

    // 辅助函数
    bool isInBlacksmith() const;       // 检查是否在铁匠铺
    bool isInVillage() const;          // 检查是否在村庄

private:
    Player& player;
    Map& map;

    // 序列化辅助函数
    void serializePlayer(std::ofstream& out);
    void serializeMap(std::ofstream& out);
    void deserializePlayer(std::ifstream& in);
    void deserializeMap(std::ifstream& in);
};

#endif // COMMAND_H