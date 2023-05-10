#ifndef TOP_GAME_MOVEABLE_HPP
#define TOP_GAME_MOVEABLE_HPP

#include <threepp/math/Vector3.hpp>
#include <threepp/math/Quaternion.hpp>
#include <threepp/math/MathUtils.hpp>
#include <cmath>


class MoveAble {
public:
    threepp::Vector3 direction{};
    threepp::Vector3 position;
    threepp::Quaternion quaternion;
    const threepp::Vector3 upDirection{0, 0, 1};

    explicit MoveAble(threepp::Vector3 startPos = {0, 0, 0}, float angle = 0);

    void setForceVector(float velocity, float dt);

    void setRotation(float angle);

    void setPosition(threepp::Vector3 &pos);

    void setBaseSpeed(float newBaseSpeed);

    void setTurnSpeed(float newTurnSpeed);

    [[nodiscard]] threepp::Vector3 getPosition() const;

    [[nodiscard]] float getRotation() const;

    [[nodiscard]] float getBaseSpeed() const;

    [[nodiscard]] float getTurnSpeed() const;

    [[nodiscard]] threepp::Vector3 getDirection() const;

    void move(float turnDirection, float dt);

    void resetPosAndRotation();

private:

    float rotation_;
    float baseSpeed_{};
    float turnSpeed_{};

    threepp::Vector3 resetPosition_{0, 0, 0};
    float resetRotation_{0};

    void rotateBy(float turnDirection);

    void moveFor();

};

#endif //TOP_GAME_MOVEABLE_HPP
