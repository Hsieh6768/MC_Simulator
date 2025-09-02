#include "EnderDragon.h"

EnderDragon::EnderDragon() {}

int EnderDragon::dropMoney(int random_number) {
    return random_number % 50 + 100;
}
