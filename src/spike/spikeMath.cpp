
#include "spike/spikeMath.hpp"

SpikeMath::SpikeMath() {
    damage_ = 100;
}

int SpikeMath::dealDamage() const {
    return damage_;
}

void SpikeMath::setNewDamage(int newDamage) {
    damage_ = newDamage;
}
