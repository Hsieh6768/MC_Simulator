#include "Enderman.h"

Enderman::Enderman() : Monster("终界使者", health_max, health_max, attack, "精英") {}

int Enderman::dropMoney(int random_number) const override {
    return DropConstants::ENDERMAN_BASE_DROP + random_number % DropConstants::ENDERMAN_DROP_RANGE;
}
