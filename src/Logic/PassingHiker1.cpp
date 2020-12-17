#include "PassingHiker1.h"


namespace turbohiker {
    void PassingHiker1::display() {}

    void PassingHiker1::update(float dTime) {}

    bool PassingHiker1::doTypeSpecificAction() { return false; }

    bool PassingHiker1::isActive() const {
        return active;
    }

    void PassingHiker1::setActive(bool _active) {
        this->active = _active;
    }

    EntityType PassingHiker1::getType() const {
        return active ? EntityType::StaticHikerActive : EntityType::StaticHikerInactive;
    }

}

