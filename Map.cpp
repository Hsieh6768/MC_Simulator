#include "Map.h"
#include <iostream>
#include <algorithm>

using namespace std;

Map::Map() : currentAreaId(0) {
    initializeMap();
}


void Map::initializeMap() {
    // 创建所有区域
    areas[0] = std::make_unique<Area>(0, VILLAGE, "村庄",
        "一个宁静的小村庄，村民们正在忙碌。\n这里是冒险的起点。", true);
    areas[1] = std::make_unique<Area>(1, BLACKSMITH, "铁匠铺",
        "铁匠正在打造武器，炉火熊熊燃烧。\n可以在这里升级装备。", true);
    areas[2] = std::make_unique<Area>(2, PLAIN, "平原",
        "广阔的平原，风吹草低见牛羊。");
    areas[3] = std::make_unique<Area>(3, MINE, "矿井",
        "废弃的矿井，深处传来奇怪的声音。");
    areas[4] = std::make_unique<Area>(4, DUNGEON, "地牢",
        "阴暗潮湿的地牢，漫步着未知的生物。");
    areas[5] = std::make_unique<Area>(5, END, "终界",
        "世界的尽头，充满了神秘的力量与无尽的虚空。");
    areas[6] = std::make_unique<Area>(6, DARK_FOREST, "黑森林入口",
        "黑暗森林的入口，树木茂密，光线昏暗。");
    areas[7] = std::make_unique<Area>(7, DEEP_FOREST, "森林深处",
        "黑森林的深处，充满了未知的危险。");
    areas[8] = std::make_unique<Area>(8, FORTRESS, "堡垒",
        "坚固的堡垒，来自地狱的怪物便驻于此。");
    areas[9] = std::make_unique<Area>(9, CAVE, "洞穴",
        "深邃的洞穴，可能藏有宝藏或怪物。");

    // 设置区域连接关系
    areas[0]->connectedAreas = { 1, 2 };      // 村庄连接铁匠、平原
    areas[1]->connectedAreas = { 0 };         // 铁匠只连接村庄
    areas[2]->connectedAreas = { 0, 3, 6 };   // 平原连接村庄、矿井、黑森林入口
    areas[3]->connectedAreas = { 2, 4 };      // 矿井连接平原、地牢
    areas[4]->connectedAreas = { 3, 5 };      // 地牢连接矿井、终界
    areas[5]->connectedAreas = { 4 };         // 终界连接地牢
    areas[6]->connectedAreas = { 2, 7, 9 };   // 黑森林入口连接平原、森林深处、洞穴
    areas[7]->connectedAreas = { 6, 8 };      // 森林深处连接黑森林入口、堡垒
    areas[8]->connectedAreas = { 7 };         // 堡垒只连接森林深处
    areas[9]->connectedAreas = { 6 };         // 洞穴只连接黑森林入口

    // 设置宝藏区域
    areas[4]->hasTreasure = true;  // 地牢有宝藏
    areas[9]->hasTreasure = true;  // 洞穴有宝藏
    areas[5]->hasTreasure = true;  // 终界有宝藏
    areas[8]->hasTreasure = true;  // 堡垒有宝藏

    // 设置初始区域为已访问
    areas[0]->visited = true;
    currentAreaId = 0;

    // 生成固定怪物
    spawnFixedMonsters();
}
void Map::spawnFixedMonsters() {
    // 清空所有区域的怪物
    for (auto& pair : areas) {
        if (pair.second) pair.second->creatures.clear();
    }

    // 为每个区域生成固定怪物
    spawnMonstersInArea(2, { "Zombie", "Zombie" });  // 平原：2只僵尸
    spawnMonstersInArea(3, { "Zombie", "Spider", "Zombie" });  // 矿井：2僵尸1蜘蛛
    spawnMonstersInArea(4, { "WitherSkeleton", "WitherSkeleton", "Spider" });  // 地牢：2凋零骷髅1蜘蛛
    spawnMonstersInArea(6, { "Spider", "Spider", "Piglin" });  // 黑森林入口：2蜘蛛1猪灵
    spawnMonstersInArea(7, { "Spider", "Enderman", "Piglin" });  // 森林深处：1蜘蛛1末影人1猪灵
    spawnMonstersInArea(8, { "Blaze", "Blaze", "WitherSkeleton" });  // 堡垒：2烈焰使者1凋零骷髅
    spawnMonstersInArea(9, { "Zombie", "Spider", "Piglin", "Zombie" });  // 洞穴：2僵尸1蜘蛛1猪灵
    spawnMonstersInArea(5, { "EnderDragon" });  // 终界：1终界龙（BOSS）

    // 安全区域没有怪物
    if (areas[0]) areas[0]->creatures.clear(); // 村庄
    if (areas[1]) areas[1]->creatures.clear(); // 铁匠铺
}
void Map::spawnMonstersInArea(int areaId, const vector<string>& monsterTypes) {
    Area* area = getArea(areaId);
    if (!area) return;

    for (const auto& monsterType : monsterTypes) {
        auto monster = createMonsterByType(monsterType);
        if (monster) {
            area->creatures.push_back(monster);
        }
    }
}

shared_ptr<Monster> Map::createMonsterByType(const string& monsterType) {
    if (monsterType == "Zombie") {
        return make_shared<Zombie>();
    }
    else if (monsterType == "Spider") {
        return make_shared<Spider>();
    }
    else if (monsterType == "Piglin") {
        return make_shared<Piglin>();
    }
    else if (monsterType == "WitherSkeleton") {
        return make_shared<WitherSkeleton>();
    }
    else if (monsterType == "Enderman") {
        return make_shared<Enderman>();
    }
    else if (monsterType == "Blaze") {
        return make_shared<Blaze>();
    }
    else if (monsterType == "EnderDragon") {
        return make_shared<EnderDragon>();
    }
    return nullptr;
}

void Map::displayMinimap() const {
    ColorManager::COLOR_PRINT("      探索地图：\n", YELLOW);

    ColorManager::COLOR_PRINT("    ╔══════════════════════════════════╗\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                       终界(5)    ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                         │        ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                       地牢(4)    ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                         │        ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                       矿井(3)    ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                         │        ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║   铁匠(1)───村庄(0)───平原(2)    ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                        ╱         ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                   黑森林入口(6)  ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                    ╱     │       ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║              洞穴(9)  森林深处(7)║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                          │       ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ║                         堡垒(8)  ║\n", YELLOW);

    ColorManager::COLOR_PRINT("    ╚══════════════════════════════════╝\n", YELLOW);
}

void Map::displayAvailableDirections() const {
    Area* area = getCurrentArea();
    if (!area || area->connectedAreas.empty()) {
        cout << "\n这里没有出口。" << endl;
        return;
    }

    cout << "\n可前往的区域：" << endl;
    for (size_t i = 0; i < area->connectedAreas.size(); i++) {
        int targetId = area->connectedAreas[i];
        Area* targetArea = getArea(targetId);
        if (targetArea) {
            string visitedMark = targetArea->visited ? "[已探索] " : "[未探索] ";
            cout << i + 1 << ". " << visitedMark << targetArea->name;
            if (targetArea->isSafe) {
                ColorManager::COLOR_PRINT(" [安全区域]", GREEN);
            }
            if (targetArea->hasTreasure) {
                ColorManager::COLOR_PRINT(" [宝藏]", PURPLE);
            }
            cout << endl;
        }
    }
}

bool Map::moveToArea(int areaId) {
    Area* currentArea = getCurrentArea();
    if (!currentArea) return false;

    // 检查是否连接
    if (find(currentArea->connectedAreas.begin(),
        currentArea->connectedAreas.end(), areaId) == currentArea->connectedAreas.end()) {
        return false;
    }

    Area* targetArea = getArea(areaId);
    if (!targetArea) return false;
    currentAreaId = areaId;
    markAreaVisited(areaId);
    return true;
}

bool Map::moveToConnectedArea(int directionIndex) {
    Area* currentArea = getCurrentArea();
    if (!currentArea || directionIndex < 0 ||
        directionIndex >= static_cast<int>(currentArea->connectedAreas.size())) {
        return false;
    }

    int targetId = currentArea->connectedAreas[directionIndex];
    return moveToArea(targetId);
}

vector<int> Map::getConnectedAreas() const {
    Area* area = getCurrentArea();
    if (area) {
        return area->connectedAreas;
    }
    return {};
}

bool Map::addCreatureToArea(int areaId, shared_ptr<Creature> creature) {
    Area* area = getArea(areaId);
    if (!area) return false;

    area->creatures.push_back(creature);
    return true;
}

bool Map::removeCreatureFromArea(int areaId, const string& creatureName) {
    Area* area = getArea(areaId);
    if (!area) return false;

    auto& creatures = area->creatures;
    auto it = find_if(creatures.begin(), creatures.end(),
        [&](const shared_ptr<Creature>& creature) {
            return creature->getName() == creatureName;
        });

    if (it != creatures.end()) {
        creatures.erase(it);
        return true;
    }

    return false;
}

vector<shared_ptr<Creature>> Map::getCreaturesInArea(int areaId) const {
    Area* area = getArea(areaId);
    if (area) {
        return area->creatures;
    }
    return {};
}

Area* Map::getArea(int areaId) const {
    auto it = areas.find(areaId);
    if (it != areas.end()) {
        return it->second.get();
    }
    return nullptr;
}

Area* Map::getCurrentArea() const {
    return getArea(currentAreaId);
}

int Map::getCurrentAreaId() const {
    return currentAreaId;
}

string Map::getAreaTypeName(AreaType type) const {
    switch (type) {
    case VILLAGE: return "村庄";
    case BLACKSMITH: return "铁匠铺";
    case PLAIN: return "平原";
    case MINE: return "矿井";
    case DUNGEON: return "地牢";
    case END: return "终界";
    case DARK_FOREST: return "黑森林";
    case DEEP_FOREST: return "森林深处";
    case FORTRESS: return "堡垒";
    case CAVE: return "洞穴";
    default: return "未知区域";
    }
}
void Map::displayCurrentPosition() const {
    Area* area = getCurrentArea();
    if (!area) return;

    cout << "[位置] " << area->name << endl;
    ColorManager::COLOR_PRINT(area->description, YELLOW);
    cout << "\n────────────────────────────────────────" << endl;

    // 敌怪
    vector<string> monsters;
    for (const auto& creature : area->creatures) {
        if (dynamic_pointer_cast<Monster>(creature)) {
            monsters.push_back(creature->getName());
        }
    }

    if (monsters.empty()) {
        cout << "敌怪: 无" << endl;
    }
    else {
        cout << "敌怪: ";
        for (size_t i = 0; i < monsters.size(); i++) {
            if (i > 0) cout << ", ";
            ColorManager::COLOR_PRINT(monsters[i], RED);
        }
        cout << endl;
    }

    displayAvailableDirections();

    cout << "────────────────────────────────────────" << endl << endl;
}
bool Map::hasMonstersInCurrentArea() const {
    Area* area = getArea(currentAreaId);
    if (!area) return false;

    for (const auto& creature : area->creatures) {
        if (dynamic_pointer_cast<Monster>(creature)) {
            return true;
        }
    }
    return false;
}

vector<shared_ptr<Monster>> Map::getMonstersInCurrentArea() const {
    vector<shared_ptr<Monster>> monsters;
    Area* area = getArea(currentAreaId);
    if (!area) return monsters;

    for (const auto& creature : area->creatures) {
        if (auto monster = dynamic_pointer_cast<Monster>(creature)) {
            monsters.push_back(monster);
        }
    }
    return monsters;
}

void Map::markAreaVisited(int areaId) {
    Area* area = getArea(areaId);
    if (area) {
        area->visited = true;
    }
}

bool Map::isAreaVisited(int areaId) const {
    Area* area = getArea(areaId);
    return area ? area->visited : false;
}

int Map::getVisitedAreaCount() const {
    int count = 0;
    for (const auto& pair : areas) {
        if (pair.second->visited) {
            count++;
        }
    }
    return count;
}

void Map::serializeMonsters(std::ofstream& out) const {
    // 写入区域数量
    int areaCount = static_cast<int>(areas.size());
    out.write(reinterpret_cast<const char*>(&areaCount), sizeof(int));

    for (const auto& pair : areas) {
        int areaId = pair.first;
        const Area* area = pair.second.get();

        // 写入区域ID
        out.write(reinterpret_cast<const char*>(&areaId), sizeof(int));

        // 写入该区域的怪物数量
        int monsterCount = 0;
        for (const auto& creature : area->creatures) {
            if (dynamic_pointer_cast<Monster>(creature)) {
                monsterCount++;
            }
        }
        out.write(reinterpret_cast<const char*>(&monsterCount), sizeof(int));

        // 写入每个怪物的信息
        for (const auto& creature : area->creatures) {
            if (auto monster = dynamic_pointer_cast<Monster>(creature)) {
                // 写入怪物类型
                string monsterType = monster->getTypeName();
                size_t typeLength = monsterType.size();
                out.write(reinterpret_cast<const char*>(&typeLength), sizeof(size_t));
                out.write(monsterType.c_str(), typeLength);

                // 写入怪物当前生命值
                int healthCur = monster->getHealthCur();
                out.write(reinterpret_cast<const char*>(&healthCur), sizeof(int));
            }
        }
    }
}

void Map::deserializeMonsters(std::ifstream& in) {
    // 清空所有区域的怪物
    for (auto& pair : areas) {
        if (pair.second) {
            pair.second->creatures.clear();
        }
    }

    // 读取区域数量
    int areaCount = 0;
    in.read(reinterpret_cast<char*>(&areaCount), sizeof(int));

    for (int i = 0; i < areaCount; i++) {
        // 读取区域ID
        int areaId = 0;
        in.read(reinterpret_cast<char*>(&areaId), sizeof(int));

        Area* area = getArea(areaId);
        if (!area) continue;

        // 读取该区域的怪物数量
        int monsterCount = 0;
        in.read(reinterpret_cast<char*>(&monsterCount), sizeof(int));

        // 读取每个怪物的信息
        for (int j = 0; j < monsterCount; j++) {
            // 读取怪物类型
            size_t typeLength = 0;
            in.read(reinterpret_cast<char*>(&typeLength), sizeof(size_t));
            vector<char> typeBuffer(typeLength);
            in.read(typeBuffer.data(), typeLength);
            string monsterType(typeBuffer.data(), typeLength);

            // 读取怪物当前生命值
            int healthCur = 0;
            in.read(reinterpret_cast<char*>(&healthCur), sizeof(int));

            // 创建怪物
            auto monster = createMonsterByType(monsterType);
            if (monster) {
                monster->setHealthCur(healthCur);
                area->creatures.push_back(monster);
            }
        }
    }
}
