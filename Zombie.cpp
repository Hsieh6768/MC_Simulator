#include "Zombie.h"

Zombie::Zombie() {}

int Zombie::dropMoney(int random_number) {
    return random_number % 3 + 1;
}
