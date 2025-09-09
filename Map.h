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

// ��������ö��
enum AreaType {
    VILLAGE,        // ��ׯ
    BLACKSMITH,     // ������
    PLAIN,          // ƽԭ
    MINE,           // ��
    DUNGEON,        // ����
    END,            // �ս�
    DARK_FOREST,    // ��ɭ�����
    DEEP_FOREST,    // ɭ���
    FORTRESS,       // ����
    CAVE            // ��Ѩ
};

// ����ṹ
struct Area {
    int id;
    AreaType type;
    std::string name;
    std::string description;
    std::vector<int> connectedAreas; // ���ӵ�����ID
    std::vector<std::shared_ptr<Creature>> creatures;
    bool visited;
    bool hasTreasure;
    bool isSafe; // ��ȫ��

    Area(int id = 0, AreaType type = VILLAGE, std::string name = "",
        std::string desc = "", bool isSafe = false)
        : id(id), type(type), name(name), description(desc),
        visited(false), hasTreasure(false), isSafe(isSafe) {}
};

class Map {
public:
    Map();
    ~Map();

    // ��ͼ����
    void initializeMap();
    void displayCurrentArea() const;
    void displayMinimap() const;
    void displayAvailableDirections() const;
    void displayCurrentPosition() const;

    // �ƶ�����
    bool moveToArea(int areaId);
    bool moveToConnectedArea(int directionIndex);
    std::vector<int> getConnectedAreas() const;

    // �������
    bool addCreatureToArea(int areaId, std::shared_ptr<Creature> creature);
    bool removeCreatureFromArea(int areaId, const std::string& creatureName);
    std::vector<std::shared_ptr<Creature>> getCreaturesInArea(int areaId) const;

    // �̶���������
    void spawnFixedMonsters(); // ���ɹ̶�����

    // ������Ϣ
    Area* getArea(int areaId);
    Area* getCurrentArea();
    int getCurrentAreaId() const;
    std::string getAreaTypeName(AreaType type) const;

    // ս�����
    bool hasMonstersInCurrentArea() const;
    std::vector<std::shared_ptr<Monster>> getMonstersInCurrentArea() const;

    // ̽�����
    void markAreaVisited(int areaId);
    bool isAreaVisited(int areaId) const;
    int getVisitedAreaCount() const;

private:
    std::map<int, Area*> areas;
    int currentAreaId;

    // �̶��������ɸ�������
    void spawnMonstersInArea(int areaId, const std::vector<std::string>& monsterTypes);
    std::shared_ptr<Monster> createMonsterByType(const std::string& monsterType);
};

#endif // MAP_H