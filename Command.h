#ifndef COMMAND_H
#define COMMAND_H

#include "Player.h"
#include "Map.h"
#include "Battle.h"
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

class Command {
public:
    Command(Player& player, Map& map);

    // 主要命令函数
    void newGame();                    // 创建新游戏
    bool saveGame(const std::string& filename); // 保存游戏
    bool loadGame(const std::string& filename); // 加载游戏
    void exitGame();                   // 退出游戏并保存进度
    bool autoSave();                   // 自动保存游戏
    void trade();                      // 装备交易与升级
    void recover();                    // 恢复玩家状态
    void battleSelection();            // 选择战斗目标
    void move();                       // 移动至其他区域
    void panel();                      // 显示玩家属性面板
    void showMap() const;                    // 显示游戏地图

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