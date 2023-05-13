
#include "spike/spikeMath.hpp"

SpikeMath::SpikeMath() {
    damage_ = 50;
}

int SpikeMath::dealDamage() const {
    return damage_;
}

void SpikeMath::setNewDamage(int newDamage) {
    damage_ = newDamage;
}
