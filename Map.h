#ifndef MAP_H
#define MAP_H

#include "Creature.h"
#include "Player.h"
#include "Monster.h"
#include "Zombie.h"
#include "Spider.h"
#include "Piglin.h"
#include "WitherSkeleton.h"
#include "Enderman.h"
#include "Blaze.h"
#include "EnderDragon.h"
#include <vector>
#include <memory>
#include <string>
#include <map>

// 区域类型枚举
enum AreaType {
    VILLAGE,        // 村庄
    BLACKSMITH,     // 铁匠铺
    PLAIN,          // 平原
    MINE,           // 矿井
    DUNGEON,        // 地牢
    END,            // 终界
    DARK_FOREST,    // 黑森林入口
    DEEP_FOREST,    // 森林深处
    FORTRESS,       // 堡垒
    CAVE            // 洞穴
};

// 区域结构
struct Area {
    int id;
    AreaType type;
    std::string name;
    std::string description;
    std::vector<int> connectedAreas; // 连接的区域ID
    std::vector<std::shared_ptr<Creature>> creatures;
    bool visited;
    bool hasTreasure;
    bool isSafe; // 安全区

    Area(int id = 0, AreaType type = VILLAGE, std::string name = "",
        std::string desc = "", bool isSafe = false)
        : id(id), type(type), name(name), description(desc),
        visited(false), hasTreasure(false), isSafe(isSafe) {}
};

class Map {
public:
    Map();
    ~Map();

    // 地图操作
    void initializeMap();
    void displayCurrentArea() const;
    void displayMinimap() const;
    void displayAvailableDirections() const;
    void displayCurrentPosition() const;

    // 移动操作
    bool moveToArea(int areaId);
    bool moveToConnectedArea(int directionIndex);
    std::vector<int> getConnectedAreas() const;

    // 生物操作
    bool addCreatureToArea(int areaId, std::shared_ptr<Creature> creature);
    bool removeCreatureFromArea(int areaId, const std::string& creatureName);
    std::vector<std::shared_ptr<Creature>> getCreaturesInArea(int areaId) const;

    // 固定怪物生成
    void spawnFixedMonsters(); // 生成固定怪物

    // 区域信息
    Area* getArea(int areaId);
    Area* getCurrentArea();
    int getCurrentAreaId() const;
    std::string getAreaTypeName(AreaType type) const;

    // 战斗相关
    bool hasMonstersInCurrentArea() const;
    std::vector<std::shared_ptr<Monster>> getMonstersInCurrentArea() const;

    // 探索相关
    void markAreaVisited(int areaId);
    bool isAreaVisited(int areaId) const;
    int getVisitedAreaCount() const;

private:
    std::map<int, Area*> areas;
    int currentAreaId;

    // 固定怪物生成辅助方法
    void spawnMonstersInArea(int areaId, const std::vector<std::string>& monsterTypes);
    std::shared_ptr<Monster> createMonsterByType(const std::string& monsterType);
};

#endif // MAP_H