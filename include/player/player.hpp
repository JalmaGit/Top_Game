#ifndef TOP_GAME_PLAYER_HPP
#define TOP_GAME_PLAYER_HPP

#include "moveAble.hpp"

class Player : public MoveAble {
public:

    explicit Player(int health = 1000);

    void setHealth(int newHealth);

    void setScore(int newScore);

    [[nodiscard]] int getHealth() const;

    [[nodiscard]] int getScore() const;

    void addScore(int newAddScore);

    void removeScore(int newRemoveScore);

    void takeDamage(int damage);

private:
    int health_;
    int score_;
};

#endif //TOP_GAME_PLAYER_HPP
