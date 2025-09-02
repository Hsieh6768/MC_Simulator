#include "Enderman.h"

Enderman::Enderman() {}

int Enderman::dropMoney(int random_number) {
    return random_number % 36 + 1;
}
