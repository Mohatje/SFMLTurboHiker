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
        // type is based on whether the hiker is active or not (have they been yelled it and yell was successful?)
        return active ? EntityType::StaticHikerActive : EntityType::StaticHikerInactive;
    }

}

