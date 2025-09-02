#include "Blaze.h"

Blaze::Blaze() {}

int Blaze::dropMoney(int random_number) {
    return random_number % 25 + 1;
}
