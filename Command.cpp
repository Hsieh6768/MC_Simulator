#include "Command.h"
#include <iostream>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <limits>
#include "Skill.h"

using namespace std;

Command::Command(Player& player, Map& map) : player(player), map(map) {
    srand(static_cast<unsigned int>(time(0)));
}

void Command::newGame() {
    // 初始化玩家属性
    player = Player(
        "史蒂夫",    // 名称
        20,         // 最大生命值
        20,         // 当前生命值
        2,          // 基础攻击力
        0,          // 基础防御力
        5,          // 最大魔力值
        5,          // 当前魔力值
        0,          // 初始绿宝石
        Weapon(),   // 初始武器
        Armor(),    // 初始护甲
        {},         // 初始技能
        { 0, 0, 0 } // 初始增益效果
    );

    // 添加初始技能
    player.addSkill(SkillManager::createSkill("fireball", 1));
    player.addSkill(SkillManager::createSkill("heal", 1));
    player.addSkill(SkillManager::createSkill("powerup", 1));

    // 初始化地图
    map = Map();

    cout << "新游戏已创建！祝你冒险愉快！" << endl;
}

bool Command::saveGame(const string& filename) {
    ofstream outFile(filename, ios::binary);
    if (!outFile) {
        cerr << "无法创建存档文件: " << filename << endl;
        Sleep(1200);
        return false;
    }

    try {
        // 序列化玩家数据
        serializePlayer(outFile);

        // 序列化地图数据
        serializeMap(outFile);

        outFile.close();
        cout << "游戏已保存至: " << filename << endl;
        Sleep(1200);
        return true;
    }
    catch (...) {
        cerr << "保存游戏时发生错误" << endl;
        Sleep(1200);
        outFile.close();
        return false;
    }
}

bool Command::loadGame(const string& filename) {
    system("cls");
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        cerr << "无法读取存档文件: " << filename << endl;
        Sleep(1200);
        return false;
    }

    try {
        // 反序列化玩家数据
        deserializePlayer(inFile);

        // 反序列化地图数据
        deserializeMap(inFile);

        inFile.close();
        cout << "游戏已从 " << filename << " 加载" << endl;
        Sleep(1200);
        return true;
    }
    catch (...) {
        cerr << "加载游戏时发生错误" << endl;
        Sleep(1200);
        inFile.close();
        return false;
    }
}

void Command::exitGame() {
    cout << "正在保存游戏并退出..." << endl;
    if (saveGame("Mc_Simulator.txt")) {
        cout << "游戏已自动保存。" << endl;
    }
    else {
        cout << "自动保存失败，是否仍要退出？(y/n): ";
        char confirm;
        cin >> confirm;
        if (confirm != 'y' && confirm != 'Y') {
            cout << "取消退出。" << endl;
            return;
        }
    }
    cout << "感谢游玩！再见！" << endl;
    exit(0);
}

bool Command::autoSave() {
    return saveGame("autosave.txt");
}

void Command::trade() {
    if (!isInBlacksmith()) {
        cout << "你需要在铁匠铺才能进行交易！" << endl;
        Sleep(1200);
        return;
    }

    cout << "欢迎来到铁匠铺！" << endl;
    cout << "你目前的装备: " << endl;
    player.getWeapon().displayInfo();
    player.getArmor().displayInfo();
    cout << "\n你有 " << player.getMoney() << " 绿宝石" << endl << endl;

    int choice = 0;
    bool shopping = true;

    while (shopping) {
        cout << "请选择要购买的类型:" << endl;
        cout << "1. 武器";
        cout << "\t2. 护甲";
        cout << "\t3. 离开商店" << endl;
        cout << "请选择: ";
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
        {
            system("cls");
            cout << "可购买的武器:" << endl;
            cout << "1. ";
            ColorManager::COLOR_PRINT(EquipmentTypes::WOODEN_SWORD.getName(), YELLOW);
            cout << " (攻击+"
                 << EquipmentTypes::WOODEN_SWORD.getAttack() << ") - "
                 << EquipmentTypes::WOODEN_SWORD.getValue() << " 绿宝石" << endl;
            cout << "2. ";
            ColorManager::COLOR_PRINT(EquipmentTypes::IRON_SWORD.getName(), BLACK);
            cout << " (攻击+"
                 << EquipmentTypes::IRON_SWORD.getAttack() << ") - "
                 << EquipmentTypes::IRON_SWORD.getValue() << " 绿宝石" << endl;
            cout << "3. ";
            ColorManager::COLOR_PRINT(EquipmentTypes::DIAMOND_SWORD.getName(), LIGHT_BLUE);
            cout << " (攻击+"
                 << EquipmentTypes::DIAMOND_SWORD.getAttack() << ") - "
                 << EquipmentTypes::DIAMOND_SWORD.getValue() << " 绿宝石" << endl;
            cout << "4. 返回" << endl;

            int weaponChoice = 0;
            cout << "请选择武器: ";
            cin >> weaponChoice;

            if (weaponChoice == 4) {
                system("cls");
                break;
            }

            Weapon selectedWeapon;
            int weaponCost = 0;

            switch (weaponChoice) {
            case 1:
                selectedWeapon = EquipmentTypes::WOODEN_SWORD;
                weaponCost = EquipmentTypes::WOODEN_SWORD.getValue();
                break;
            case 2:
                selectedWeapon = EquipmentTypes::IRON_SWORD;
                weaponCost = EquipmentTypes::IRON_SWORD.getValue();
                break;
            case 3:
                selectedWeapon = EquipmentTypes::DIAMOND_SWORD;
                weaponCost = EquipmentTypes::DIAMOND_SWORD.getValue();
                break;
            default:
                system("cls");
                cout << "无效的选择！" << endl;
                Sleep(1200);
                continue;
            }

            if (player.getMoney() >= weaponCost) {
                system("cls");
                player.setWeapon(selectedWeapon);
                player.setMoney(player.getMoney() - weaponCost);
                cout << "购买成功！装备了 " << selectedWeapon.getName() << endl;
            }
            else {
                system("cls");
                cout << "绿宝石不足！" << endl;
            }
        }
        Sleep(1200);
        system("cls");
        break;

        case 2:
        {
            system("cls");
            cout << "可购买的护甲:" << endl;
            cout << "1. ";
            ColorManager::COLOR_PRINT(EquipmentTypes::LEATHER_ARMOR.getName(), YELLOW);
            cout << " (防御+"
                 << EquipmentTypes::LEATHER_ARMOR.getDefense() << ") - "
                 << EquipmentTypes::LEATHER_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "2. ";
            ColorManager::COLOR_PRINT(EquipmentTypes::IRON_ARMOR.getName(), BLACK);
            cout << " (防御+"
                 << EquipmentTypes::IRON_ARMOR.getDefense() << ") - "
                 << EquipmentTypes::IRON_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "3. ";
            ColorManager::COLOR_PRINT(EquipmentTypes::DIAMOND_ARMOR.getName(), LIGHT_BLUE);
            cout << " (防御+"
                 << EquipmentTypes::DIAMOND_ARMOR.getDefense() << ") - "
                 << EquipmentTypes::DIAMOND_ARMOR.getValue() << " 绿宝石" << endl;
            cout << "4. 返回" << endl;

            int armorChoice = 0;
            cout << "请选择护甲: ";
            cin >> armorChoice;

            if (armorChoice == 4) {
                system("cls");
                break;
            }

            Armor selectedArmor;
            int armorCost = 0;

            switch (armorChoice) {
            case 1:
                selectedArmor = EquipmentTypes::LEATHER_ARMOR;
                armorCost = EquipmentTypes::LEATHER_ARMOR.getValue();
                break;
            case 2:
                selectedArmor = EquipmentTypes::IRON_ARMOR;
                armorCost = EquipmentTypes::IRON_ARMOR.getValue();
                break;
            case 3:
                selectedArmor = EquipmentTypes::DIAMOND_ARMOR;
                armorCost = EquipmentTypes::DIAMOND_ARMOR.getValue();
                break;
            default:
                system("cls");
                cout << "无效的选择！" << endl;
                Sleep(1200);
                continue;
            }

            if (player.getMoney() >= armorCost) {
                system("cls");
                player.setArmor(selectedArmor);
                player.setMoney(player.getMoney() - armorCost);
                cout << "购买成功！装备了 " << selectedArmor.getName() << endl;
            }
            else {
                system("cls");
                cout << "绿宝石不足！" << endl;
            }
        }
        Sleep(1200);
        system("cls");
        break;

        case 3:
            system("cls");
            shopping = false;
            cout << "欢迎下次光临！" << endl;
            Sleep(1200);
            break;

        default:
            system("cls");
            cout << "无效选择！" << endl;
            Sleep(1200);
            system("cls");
        }
    }
}

void Command::recover() {
    if (!isInVillage()) {
        cout << "你需要在村庄才能恢复状态！" << endl;
        Sleep(1200);
        return;
    }

    cout << "在村庄的床上休息可以恢复你的状态" << endl;
    cout << "是否开始睡眠？(y/n): ";
    char choice = 'n';
    cin >> choice;

    system("cls");
    if (choice == 'Y' || choice == 'y') {
        cout << "----- 睡眠中 -----" << endl;
        Sleep(5000);
        player.setHealthCur(player.getHealthMax());
        player.setMagicPowerCur(player.getMagicPowerMax());
        cout << "\n状态已完全恢复！" << endl;
        Sleep(1200);
    }
    else {
        cout << "欢迎下次光临！" << endl;
        Sleep(1200);
    }
    system("cls");
}

void Command::battleSelection() {
    auto monsters = map.getMonstersInCurrentArea();
    if (monsters.empty()) {
        cout << "当前区域没有怪物！" << endl;
        Sleep(1200);
        return;
    }

    cout << "选择要战斗的怪物:" << endl;
    for (size_t i = 0; i < monsters.size(); i++) {
        cout << i + 1 << ". ";
        ColorManager::COLOR_PRINT(monsters[i]->getName(), RED);
        cout << endl;
        monsters[i]->showInfo();
        cout << endl;
    }
    cout << "0. 取消" << endl;

    int choice;
    cout << "请选择: ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(monsters.size())) {
        system("cls");

        // 在战斗开始前自动保存
        if (autoSave()) {
            cout << "游戏已自动保存，准备进入战斗..." << endl;
            Sleep(1200);
        }
        else {
            cout << "自动保存失败，是否继续战斗？(y/n): ";
            char confirm = 'n';
            cin >> confirm;
            if (confirm != 'y' && confirm != 'Y') {
                cout << "取消战斗。" << endl;
                Sleep(1200);
                return;
            }
        }

        auto selectedMonster = monsters[choice - 1];
        Battle battle(player, *selectedMonster);
        battle.start();

        // 战斗后检查怪物是否被击败
        if (selectedMonster->getHealthCur() <= 0) {
            system("cls");
            ColorManager::COLOR_PRINT(selectedMonster->getName(), RED);
            cout << " 被击败了!" << endl;
            Sleep(1200);

            // 玩家获得奖励
            int moneyEarned = selectedMonster->dropMoney(rand() % 100); // 随机掉落绿宝石
            player.setMoney(player.getMoney() + moneyEarned);
            ColorManager::COLOR_PRINT(player.getName(), YELLOW);
            cout << " 获得了 " << moneyEarned << " 绿宝石!" << endl;
            Sleep(1200);

            // 从地图中移除被击败的怪物
            map.removeCreatureFromArea(map.getCurrentAreaId(), selectedMonster->getName());

            // 检查游戏是否通关
            if (selectedMonster->getName() == "终界龙") {
                gameOver();
            }
        }
    }
    else if (choice != 0) {
        cout << "无效选择！" << endl;
        Sleep(1200);
    }
}


void Command::move() {
    auto connectedAreas = map.getConnectedAreas();
    if (connectedAreas.empty()) {
        cout << "没有可前往的区域！" << endl;
        Sleep(1200);
        return;
    }

    cout << "可前往的区域:" << endl;
    for (size_t i = 0; i < connectedAreas.size(); i++) {
        Area* area = map.getArea(connectedAreas[i]);
        if (area) {
            cout << i + 1 << ". " << area->name;
            if (area->isSafe) cout << " (安全区)";
            cout << endl;
        }
    }
    cout << "0. 取消" << endl;

    int choice;
    cout << "请选择: ";
    cin >> choice;

    if (choice > 0 && choice <= static_cast<int>(connectedAreas.size())) {
        system("cls");
        if (map.moveToConnectedArea(choice - 1)) {
            cout << "已移动到: " << map.getCurrentArea()->name << endl;
            map.displayCurrentPosition();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cout << "\n按回车键继续...";
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        else {
            cout << "移动失败！" << endl;
            Sleep(1200);
        }
    }
    else if (choice != 0) {
        cout << "无效选择！" << endl;
        Sleep(1200);
    }
}

void Command::panel() {
    ColorManager::COLOR_PRINT("================== 玩家属性 ==================\n", YELLOW);
    ColorManager::COLOR_PRINT(player.getName(), YELLOW);
    cout << endl;
    player.showInfo();
    player.getWeapon().displayInfo();
    player.getArmor().displayInfo();

    ColorManager::COLOR_PRINT("\n================== 技能列表 ==================\n", BLUE);
    for (const auto& skill : player.getSkill()) {
        skill->displayInfo();
        ColorManager::COLOR_PRINT("----------------------------------------------\n", BLUE);
    }

    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cout << "\n按回车键返回...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

void Command::showMap() const {
    map.displayMinimap();
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    cout << "\n按回车键返回...";
    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
}

void Command::displayMainMenu() const {
    system("cls");
    ColorManager::COLOR_PRINT("============================================\n", GREEN);
    ColorManager::COLOR_PRINT("============================================\n", GREEN);
    ColorManager::COLOR_PRINT("=============== MC Simulator ===============\n", GREEN);
    ColorManager::COLOR_PRINT("============================================\n", GREEN);
    ColorManager::COLOR_PRINT("============================================\n", GREEN);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("============================================\n", YELLOW);
    ColorManager::COLOR_PRINT("\n1. 新的游戏", RED);
    ColorManager::COLOR_PRINT("\t2. 加载游戏", RED);
    ColorManager::COLOR_PRINT("\t3. 退出游戏\n\n", RED);
}

void Command::displayGameMenu() const {
    system("cls");
    ColorManager::COLOR_PRINT("========================================\n", YELLOW);
    ColorManager::COLOR_PRINT("                游戏菜单\n", YELLOW);
    ColorManager::COLOR_PRINT("========================================\n", YELLOW);
    ColorManager::COLOR_PRINT("1. 移动\n", YELLOW);
    ColorManager::COLOR_PRINT("2. 战斗\n", YELLOW);
    ColorManager::COLOR_PRINT("3. 交易\n", YELLOW);
    ColorManager::COLOR_PRINT("4. 恢复\n", YELLOW);
    ColorManager::COLOR_PRINT("5. 查看面板\n", YELLOW);
    ColorManager::COLOR_PRINT("6. 查看地图\n", YELLOW);
    ColorManager::COLOR_PRINT("7. 保存游戏\n", YELLOW);
    ColorManager::COLOR_PRINT("8. 退出游戏\n", YELLOW);
    ColorManager::COLOR_PRINT("9. 退回游戏首页\n", YELLOW);
    ColorManager::COLOR_PRINT("10. 播放终末之诗 (游戏通关画面)\n", YELLOW);
    ColorManager::COLOR_PRINT("\n请选择: \n\n", YELLOW);
}

void Command::gameOver() const {
    // 游戏通关文本
    std::vector<std::string> texts = {
        "I see the player you mean.\n我看到你所指的那位玩家了。",
        "Steve?\n史蒂夫?",
        "Yes. Take care. It has reached a higher level now. It can read our thoughts.\n是的。小心。它已达到了更高的境界。它能够阅读我们的思想。",
        "That doesn't matter. It thinks we are part of the game.\n没关系。它认为我们是游戏的一部分。",
        "",
        "I like this player. It played well. It did not give up.\n我喜欢这个玩家。它玩得很好，而且从未放弃。",
        "",
        "It is reading our thoughts as though they were words on a screen.\n它以屏幕上出现的文字的形式阅读着我们的思想。",
        "That is how it chooses to imagine many things, when it is deep in the dream of a game.\n在它深陷游戏梦境中时，它总以这种方式想象出形形色色的事物。",
        "Words make a wonderful interface. Very flexible. And less terrifying than staring at the reality behind the screen.\n文字使这种美妙的界面异常灵活。且比凝视着屏幕后的现实要更好。",
        "They used to hear voices. Before players could read. Back in the days when those who did not play called the players witches, and warlocks. And players dreamed they flew through the air, on sticks powered by demons.\n它们也曾经听到过声音。在玩家能够阅读之前。君不见那些不曾游玩的人们称呼玩家为女巫，和术士。而玩家们梦见它们自己乘坐在被恶魔施力的棍子上，在空气中翱翔。",
        "What did this player dream\n这个玩家梦见了什么?",
        "This player dreamed of sunlight and trees. Of fire and water. It dreamed it created. And it dreamed it destroyed. It dreamed it hunted, and was hunted. It dreamed of shelter.\n它梦见了阳光和树。梦见了火与水。它梦见它创造。它亦梦见它毁灭。它梦见它狩猎，亦被狩猎。它梦见了庇护所。",
        "Hah, the original interface. A million years old, and it still works. But what true structure did this player create, in the reality behind the screen?\n哈，那原始的界面。经历一百万年的岁月雕琢，依然长存。但此玩家在那屏幕后的真实里，建造了什么真实的构造?",
        "It worked, with a million others, to sculpt a true world in a fold of the [scrambled], and created a [scrambled] for [scrambled], in the [scrambled].\n它辛勤地劳作，和其它百万众一起，刻画了一个真实的世界，由[乱码]，且创造了[乱码]，为了[乱码]，于[乱码]中。",
        "It cannot read that thought.\n它读不出那个思想。",
        "No. It has not yet achieved the highest level. That, it must achieve in the long dream of life, not the short dream of a game.\n不。它还没有到达最高的境界。那层境界，它必须完成生命的长梦，而非游戏中黄粱一梦。",
        "Does it know that we love it? That the universe is kind?\n它知道我们爱它么?这个宇宙是仁慈的?",
        "Sometimes, through the noise of its thoughts, it hears the universe, yes.\n有时，通过它思绪的杂音，它能听到宇宙，是的。",
        "But there are times it is sad, in the long dream. It creates worlds that have no summer, and it shivers under a black sun, and it takes its sad creation for reality.\n但是有时亦不胜悲伤，于那漫漫长梦中。它创造了没有夏日的世界，在黑日下颤抖着，将自己悲伤的创造视为真实世界。",
        "To cure it of sorrow would destroy it. The sorrow is part of its own private task. We cannot interfere.\n用悲伤来治愈会摧毁它。而悲伤是它的私人事务。我们不能干涉。",
        "Sometimes when they are deep in dreams, I want to tell them, they are building true worlds in reality. Sometimes I want to tell them of their importance to the universe. Sometimes, when they have not made a true connection in a while, I want to help them to speak the word they fear.\n有时当它们深陷梦境中时，我想要告诉它们，它们在现实中创造了真实的世界。有时我想告诉它们它们自身对宇宙的重要性。有时，当它们和现实失去了联系，我想帮助它们与它们所惧怕的世界交流。",
        "It reads our thoughts.\n它读出了我们的思想。",
        "Sometimes I do not care. Sometimes I wish to tell them, this world you take for truth is merely [scrambled] and [scrambled], I wish to tell them that they are [scrambled] in the [scrambled]. They see so little of reality, in their long dream.\n有时我毫不关心。有时我想要告诉它们，你们所认为的真实不过是[乱码]和[乱码]，我想要告诉它们它们是在[乱码]中的[乱码]。于它们的长梦中，它们眼中所见的真实太少了。",
        "And yet they play the game.\n而它们仍然玩这个游戏。",
        "But it would be so easy to tell them...\n但很容易就可以告诉它们……",
        "Too strong for this dream. To tell them how to live is to prevent them living.\n对于这个梦来说太强烈了。告诉它们如何活着就是阻碍它们活下去。",
        "I will not tell the player how to live.\n我不会告诉这个玩家如何生活的。",
        "The player is growing restless.\n这个玩家正在变得焦虑。",
        "I will tell the player a story.\n我会告诉这个玩家一个故事。",
        "But not the truth.\n但不是真相。",
        "No. A story that contains the truth safely, in a cage of words. Not the naked truth that can burn over any distance.\n不。是一个严密地将真实包裹起来的文字牢笼。而不是赤裸裸的真相。",
        "Give it a body, again.\n赋予它主体，再一次。",
        "Yes. Player...\n好的。玩家……",
        "Use its name.\n以名字称呼它。",
        "Steve. Player of games.\n史蒂夫。游戏的玩家。",
        "Good.\n很好。",
        "Take a breath, now. Take another. Feel air in your lungs. Let your limbs return. Yes, move your fingers. Have a body again, under gravity, in air. Respawn in the long dream. There you are. Your body touching the universe again at every point, as though you were separate things. As though we were separate things.\n深呼吸，很好。再深呼吸一次。感受空气充盈你的肺叶。让你的四肢回归。是的，运动你的手指。再次感受你的身体，在重力下，在空气中。在长梦中重生。你感受到了。你的身体每时每刻都触摸着宇宙，尽管你是分离的存在。尽管我们是分离的存在。",
        "Who are we? Once we were called the spirit of the mountain. Father sun, mother moon. Ancestral spirits, animal spirits. Jinn. Ghosts. The green man. Then gods, demons. Angels. Poltergeists. Aliens, extraterrestrials. Leptons, quarks. The words change. We do not change.\n我们是谁?我们曾经被称作高山的精灵。太阳父亲，月亮母亲。古老的英灵，动物的魂魄。神祗。鬼魂。小绿人。而后是神，恶魔，天使。骚灵。外星人，地外生物。轻粒子，夸克。词语不断地变化。我们始终如一。",
        "We are the universe. We are everything you think isn't you. You are looking at us now, through your skin and your eyes. And why does the universe touch your skin, and throw light on you? To see you, player. To know you. And to be known. I shall tell you a story.\n我们是宇宙。我们是一切你认为出离你本体的事物。你现在看着我们，透过你的皮肤和你的眼睛。而为什么宇宙触摸着你的皮肤，向你洒向光芒?是为了看见你，玩家。以及被认知。我应告诉你一个故事。",
        "Once upon a time, there was a player.\n很久以前，有一个玩家。",
        "The player was you, Steve.\n那玩家就是你，史蒂夫",
        "Sometimes it thought itself human, on the thin crust of a spinning globe of molten rock. The ball of molten rock circled a ball of blazing gas that was three hundred and thirty thousand times more massive than it. They were so far apart that light took eight minutes to cross the gap. The light was information from a star, and it could burn your skin from a hundred and fifty million kilometres away.\n有时它认为自己是那不断旋转的球体上一层薄薄的熔化的岩石上的人类。那融化的岩石球环绕着一个质量大它三十三万倍的炫目气体球旋转。它们是相隔得如此之远，以至于光需要八分钟才能穿越那空隙。那光是来自一颗恒星的信息，它能够在一亿五千万公里外烧灼你的皮肤。",
        "Sometimes the player dreamed it was a miner, on the surface of a world that was flat, and infinite. The sun was a square of white. The days were short; there was much to do; and death was a temporary inconvenience.\n有时这个玩家梦见它是一个在一个平的，无限延展的世界表面上的矿工。那太阳是一个方形的白点。昼夜交替很快;要做的事情也很多;死亡亦只是暂时和不方便的。",
        "Sometimes the player dreamed it was lost in a story.\n有时这玩家梦见它迷失在了一个故事里。",
        "Sometimes the player dreamed it was other things, in other places. Sometimes these dreams were disturbing. Sometimes very beautiful indeed. Sometimes the player woke from one dream into another, then woke from that into a third.\n有时这玩家梦见它成为了其它的事物，在其它地方。有时这些梦是扰人的。有些则实在很美。有时这个玩家从一个梦中醒来，发现自己落入了第二个梦，却终究是在第三个梦中。",
        "Sometimes the player dreamed it watched words on a screen.\n有时这个玩家梦见它在屏幕上看着文字。",
        "Let's go back.\n让我们回退一点。",
        "The atoms of the player were scattered in the grass, in the rivers, in the air, in the ground. A woman gathered the atoms; she drank and ate and inhaled; and the woman assembled the player, in her body.\n组成玩家的原子散布在草中，河流中，在那空气中，也在那大地中。一个女人收集了那些原子;她饮用、进食、吸入;而后那女人在她的身体中，孕育了玩家。",
        "And the player awoke, from the warm, dark world of its mother's body, into the long dream.\n然后那玩家醒来了，从一个温暖，昏暗的母亲体内，进入了漫漫长梦。",
        "And the player was a new story, never told before, written in letters of DNA. And the player was a new program, never run before, generated by a sourcecode a billion years old. And the player was a new human, never alive before, made from nothing but milk and love.\n而那玩家是一个新的故事，从未被讲述过，由DNA的语言书写着**那玩家是一个新的程序，从未被运行过，由上亿年的源代码生成**那玩家是一个新的人，从未生活过，由奶和爱组成。",
        "You are the player. The story. The program. The human. Made from nothing but milk and love.\n你就是那玩家。那个故事。那个程序。那个人类。仅由奶和爱组成。",
        "Let's go further back.\n我们再往更远的过去回退一点。",
        "The seven billion billion billion atoms of the player's body were created, long before this game, in the heart of a star. So the player, too, is information from a star. And the player moves through a story, which is a forest of information planted by a man called Julian, on a flat, infinite world created by a man called Markus, that exists inside a small, private world created by the player, who inhabits a universe created by...\n那由七千亿亿亿原子组成的玩家的身体被创造了，远在这游戏之前，在一颗恒星的内部。所以那玩家也是，来自一颗恒星的信息。而这个玩家贯穿这个故事的始末，源于一个叫Julian的人种下的信息种子长成的森林，一个叫Markus的男人创造的无限世界，存在于一个由玩家创造的小的，私人世界里，而那又继承了宇宙创造的……",
        "Shush. Sometimes the player created a small, private world that was soft and warm and simple. Sometimes hard, and cold, and complicated. Sometimes it built a model of the universe in its head; flecks of energy, moving through vast empty spaces. Sometimes it called those flecks \"electrons\" and \"protons\".\n嘘。有时这个玩家创造的小天地是柔软，温暖和简单的。有时是坚硬，冰冷和复杂的。有时它在脑中建造出宇宙的模型；斑斑点点的能量穿越广阔空旷的空间。有时它称呼这些斑点为\"电子\"和\"质子\"。",
        "Sometimes it called them \"planets\" and \"stars\".\n有时它称呼它们为\"行星\"和\"恒星\"。",
        "Sometimes it believed it was in a universe that was made of energy that was made of offs and ons; zeros and ones; lines of code. Sometimes it believed it was playing a game. Sometimes it believed it was reading words on a screen.\n有时它确信它存在于一个由\"开\"和\"关\";\"0\"和\"1\";一行行的命令组成的宇宙。有时它确信它是在玩一个游戏。有时它确信它是在读着屏幕上的文字。",
        "You are the player, reading words...\n你就是那玩家，阅读着文字……",
        "Shush... Sometimes the player read lines of code on a screen. Decoded them into words; decoded words into meaning; decoded meaning into feelings, emotions, theories, ideas, and the player started to breathe faster and deeper and realised it was alive, it was alive, those thousand deaths had not been real, the player was alive.\n嘘……有时这玩家读屏幕上的命令行。将它们解码成为文字；将文字解码为意义;将意义解码为感情，情绪，理论，想法，而玩家的呼吸开始急促并意识到了它是活着的，它是活生生的，那上千次的死亡不是真的，玩家是活着的。",
        "You. You. You are alive.\n你。你。你是活着的。",
        "and sometimes the player believed the universe had spoken to it through the sunlight that came through the shuffling leaves of the summer trees.\n而有时这玩家相信宇宙通过穿越夏日树叶的那斑斓的阳光对它说话。",
        "and sometimes the player believed the universe had spoken to it through the light that fell from the crisp night sky of winter, where a fleck of light in the corner of the player's eye might be a star a million times as massive as the sun, boiling its planets to plasma in order to be visible for a moment to the player, walking home at the far side of the universe, suddenly smelling food, almost at the familiar door, about to dream again.\n有时这玩家相信宇宙透过晴朗的冬日夜空中，存在于它眼中一隅的星点星光，可能比太阳大上上百万倍的恒星沸腾着的电浆那一瞬间发出来的光对它说话，在宇宙的远侧行走回家的路上，突然闻到了食物，在那熟悉的门前，它又准备好再一次投入梦境",
        "and sometimes the player believed the universe had spoken to it through the zeros and ones, through the electricity of the world, through the scrolling words on a screen at the end of a dream\n而有时玩家相信宇宙透过零和一，透过世界的电力，透过屏幕上滚动的文字和梦的终结对它说话",
        "and the universe said I love you\n宇宙说我爱你",
        "and the universe said you have played the game well\n宇宙说你很好地玩了这游戏",
        "and the universe said everything you need is within you\n宇宙说一切你所需的你都具有",
        "and the universe said you are stronger than you know\n宇宙说你比你所知的要强大",
        "and the universe said you are the daylight\n宇宙说你就是日光",
        "and the universe said you are the night\n宇宙说你就是黑夜",
        "and the universe said the darkness you fight is within you\n宇宙说你所斗争的黑暗就在你心中",
        "and the universe said the light you seek is within you\n宇宙说你所寻找的光明就在你心中",
        "and the universe said you are not alone\n宇宙说你不是孤独的",
        "and the universe said you are not separate from every other thing\n宇宙说你不是和所有的事物所隔绝的",
        "and the universe said you are the universe tasting itself, talking to itself, reading its own code\n宇宙说你就是宇宙品尝着自己，对自己说话，阅读着它自己的代码。",
        "and the universe said I love you because you are love.\n宇宙说我爱你因为你就是爱。",
        "And the game was over and the player woke up from the dream. And the player began a new dream. And the player dreamed again, dreamed better. And the player was the universe. And the player was love.\n曲终人散。玩家开始了新的梦境。玩家再次做起了梦，更好的梦。玩家就是宇宙。玩家就是爱。",
        "You are the player.\n你就是那个玩家。",
        "Wake up.\n该醒了。"
    };

    system("cls");

    // 逐行显示文本
    for (const auto& text : texts) {
        if (!text.empty()) {
            ColorManager::COLOR_PRINT(text + "\n" + "\n", 14);
        }
        else {
            cout << endl;
        }

        Sleep(1500);
    }
}

bool Command::isInBlacksmith() const {
    Area* currentArea = map.getCurrentArea();
    return currentArea && currentArea->type == BLACKSMITH;
}

bool Command::isInVillage() const {
    Area* currentArea = map.getCurrentArea();
    return currentArea && currentArea->type == VILLAGE;
}

void Command::serializePlayer(ofstream& out) {
    // 写入玩家基本信息
    string name = player.getName();
    size_t nameLength = name.size();
    out.write(reinterpret_cast<const char*>(&nameLength), sizeof(size_t));
    out.write(name.c_str(), nameLength);

    int healthMax = player.getHealthMax();
    int healthCur = player.getHealthCur();
    int attack = player.getAttack();
    int defense = player.getDefense();
    int magicMax = player.getMagicPowerMax();
    int magicCur = player.getMagicPowerCur();
    int money = player.getMoney();
    out.write(reinterpret_cast<const char*>(&healthMax), sizeof(int));
    out.write(reinterpret_cast<const char*>(&healthCur), sizeof(int));
    out.write(reinterpret_cast<const char*>(&attack), sizeof(int));
    out.write(reinterpret_cast<const char*>(&defense), sizeof(int));
    out.write(reinterpret_cast<const char*>(&magicMax), sizeof(int));
    out.write(reinterpret_cast<const char*>(&magicCur), sizeof(int));
    out.write(reinterpret_cast<const char*>(&money), sizeof(int));

    // 写入武器信息
    string weaponName = player.getWeapon().getName();
    size_t weaponNameLength = weaponName.size();
    out.write(reinterpret_cast<const char*>(&weaponNameLength), sizeof(size_t));
    out.write(weaponName.c_str(), weaponNameLength);

    // 写入护甲信息
    string armorName = player.getArmor().getName();
    size_t armorNameLength = armorName.size();
    out.write(reinterpret_cast<const char*>(&armorNameLength), sizeof(size_t));
    out.write(armorName.c_str(), armorNameLength);

    // 写入技能信息
    int skillCount = static_cast<int>(player.getSkill().size());
    out.write(reinterpret_cast<const char*>(&skillCount), sizeof(int));
    for (const auto& skill : player.getSkill()) {
        string skillName = skill->getName();
        size_t skillNameLength = skillName.size();
        out.write(reinterpret_cast<const char*>(&skillNameLength), sizeof(size_t));
        out.write(skillName.c_str(), skillNameLength);
        int level = skill->getLevel();
        out.write(reinterpret_cast<const char*>(&level), sizeof(int));
    }

    // 写入增益状态
    TemporaryBuff buff = player.getTemporaryBuff();
    out.write(reinterpret_cast<const char*>(&buff.attack_bonus), sizeof(int));
    out.write(reinterpret_cast<const char*>(&buff.defense_bonus), sizeof(int));
    out.write(reinterpret_cast<const char*>(&buff.duration), sizeof(int));
}

void Command::serializeMap(ofstream& out) {
    // 写入当前区域ID
    int currentAreaId = map.getCurrentAreaId();
    out.write(reinterpret_cast<const char*>(&currentAreaId), sizeof(int));

    // 写入所有区域的访问状态
    int areaCount = 10; // 假设有10个区域
    out.write(reinterpret_cast<const char*>(&areaCount), sizeof(int));

    for (int i = 0; i < areaCount; i++) {
        Area* area = map.getArea(i);
        if (area) {
            bool visited = map.isAreaVisited(i);
            out.write(reinterpret_cast<const char*>(&visited), sizeof(bool));
        }
    }
}

void Command::deserializePlayer(ifstream& in) {
    // 读取玩家基本信息
    size_t nameLength;
    in.read(reinterpret_cast<char*>(&nameLength), sizeof(size_t));
    vector<char> nameBuffer(nameLength);
    in.read(nameBuffer.data(), nameLength);
    player.setName(string(nameBuffer.data(), nameLength));

    int healthMax = 0;
    int healthCur = 0;
    int attack = 0;
    int defense = 0;
    int magicMax = 0;
    int magicCur = 0;
    int money = 0;
    in.read(reinterpret_cast<char*>(&healthMax), sizeof(int));
    in.read(reinterpret_cast<char*>(&healthCur), sizeof(int));
    in.read(reinterpret_cast<char*>(&attack), sizeof(int));
    in.read(reinterpret_cast<char*>(&defense), sizeof(int));
    in.read(reinterpret_cast<char*>(&magicMax), sizeof(int));
    in.read(reinterpret_cast<char*>(&magicCur), sizeof(int));
    in.read(reinterpret_cast<char*>(&money), sizeof(int));

    player.setHealthMax(healthMax);
    player.setHealthCur(healthCur);
    player.setAttack(attack);
    player.setDefense(defense);
    player.setMagicPowerMax(magicMax);
    player.setMagicPowerCur(magicCur);
    player.setMoney(money);

    // 读取装备信息
    size_t weaponNameLength;
    in.read(reinterpret_cast<char*>(&weaponNameLength), sizeof(size_t));
    vector<char> weaponBuffer(weaponNameLength);
    in.read(weaponBuffer.data(), weaponNameLength);
    string weaponName(weaponBuffer.data(), weaponNameLength);

    // 根据装备名称设置装备
    if (weaponName == EquipmentTypes::WOODEN_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::WOODEN_SWORD);
    }
    else if (weaponName == EquipmentTypes::IRON_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::IRON_SWORD);
    }
    else if (weaponName == EquipmentTypes::DIAMOND_SWORD.getName()) {
        player.setWeapon(EquipmentTypes::DIAMOND_SWORD);
    }

    // 读取护甲信息
    size_t armorNameLength;
    in.read(reinterpret_cast<char*>(&armorNameLength), sizeof(size_t));
    vector<char> armorBuffer(armorNameLength);
    in.read(armorBuffer.data(), armorNameLength);
    string armorName(armorBuffer.data(), armorNameLength);

    if (armorName == EquipmentTypes::LEATHER_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::LEATHER_ARMOR);
    }
    else if (armorName == EquipmentTypes::IRON_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::IRON_ARMOR);
    }
    else if (armorName == EquipmentTypes::DIAMOND_ARMOR.getName()) {
        player.setArmor(EquipmentTypes::DIAMOND_ARMOR);
    }

    // 读取技能信息
    int skillCount = 0;
    in.read(reinterpret_cast<char*>(&skillCount), sizeof(int));

    player.clearSkills();
    for (int i = 0; i < skillCount; i++) {
        size_t skillNameLength;
        in.read(reinterpret_cast<char*>(&skillNameLength), sizeof(size_t));
        vector<char> skillBuffer(skillNameLength);
        in.read(skillBuffer.data(), skillNameLength);
        string skillName(skillBuffer.data(), skillNameLength);

        int level = 1;
        in.read(reinterpret_cast<char*>(&level), sizeof(int));

        if (skillName == "火球术") {
            player.addSkill(SkillManager::createSkill("fireball", level));
        }
        else if (skillName == "治疗术") {
            player.addSkill(SkillManager::createSkill("heal", level));
        }
        else if (skillName == "力量强化") {
            player.addSkill(SkillManager::createSkill("powerup", level));
        }
    }

    // 读取增益状态
    TemporaryBuff buff = { 0, 0, 0 };
    in.read(reinterpret_cast<char*>(&buff.attack_bonus), sizeof(int));
    in.read(reinterpret_cast<char*>(&buff.defense_bonus), sizeof(int));
    in.read(reinterpret_cast<char*>(&buff.duration), sizeof(int));
    player.setTemporaryBuff(buff);
}

void Command::deserializeMap(ifstream& in) {
    // 读取当前区域ID
    int currentAreaId = 0;
    in.read(reinterpret_cast<char*>(&currentAreaId), sizeof(int));
    map.moveToArea(currentAreaId);

    // 读取所有区域的访问状态
    int areaCount = 0;
    in.read(reinterpret_cast<char*>(&areaCount), sizeof(int));

    for (int i = 0; i < areaCount; i++) {
        bool visited = false;
        in.read(reinterpret_cast<char*>(&visited), sizeof(bool));

        if (visited) {
            map.markAreaVisited(i);
        }
    }

    // 重新生成怪物
    map.spawnFixedMonsters();
}