#ifndef TOP_GAME_SPIKEMATH_HPP
#define TOP_GAME_SPIKEMATH_HPP

class SpikeMath {
public:
    explicit SpikeMath();

    void setNewDamage (int newDamage);

    [[nodiscard]] int dealDamage() const;

private:
    int damage_;

};

#endif //TOP_GAME_SPIKEMATH_HPP
