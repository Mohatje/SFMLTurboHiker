#include "Player.h"
#include "Random.h"


namespace turbohiker {
    void Player::display() {    }

    void Player::update(float dTime) {    }

    bool Player::yellAtObstacle() {
        return Random::randFloat() >= 0.50;
    }

    bool Player::doTypeSpecificAction() {
        return false;
    }


}
