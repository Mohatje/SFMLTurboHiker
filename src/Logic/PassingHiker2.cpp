#include "PassingHiker2.h"
#include "Random.h"


namespace turbohiker {
    void PassingHiker2::display() {}

    void PassingHiker2::update(float dTime) {}

    bool PassingHiker2::doTypeSpecificAction() { return false; }

    bool PassingHiker2::isActive() const {
        return active;
    }

    void PassingHiker2::setActive(bool _active) {
        this->active = _active;
    }

    EntityType PassingHiker2::getType() const {
        return active ? EntityType::MovingHikerActive : EntityType::MovingHikerInactive;
    }

    void PassingHiker2::spawn(double playerY) {
        int a = turbohiker::Random::randInt(-4, 4);
        int minY = static_cast<int>(playerY + 0.5) + 8;
        int b = turbohiker::Random::randInt(minY, minY + 5);
        double x, y;
        a < 4 ? x = a + 0.5 : x = a - 0.5;
        y = b + 0.5;
        setPosition( { x, y } );
    }

}
