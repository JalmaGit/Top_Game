
#include "coin/coinMath.hpp"

CoinMath::CoinMath() {
    points_ = 100;
}

void CoinMath::setPossiblePositions(const std::vector<threepp::Vector3> &newPossiblePositions) {
    possiblePositions_ = newPossiblePositions;
}

int CoinMath::givePoints() const {
    return points_;
}

threepp::Vector3 CoinMath::getRandomNewPosition() {
    return possiblePositions_[1];
}
