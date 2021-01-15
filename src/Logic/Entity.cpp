#include "Entity.h"

namespace turbohiker {

    const std::pair<double, double> &Entity::getPosition() const {
        return position;
    }

    const std::pair<double, double> &Entity::getVelocity() const {
        return velocity;
    }

    const std::pair<double, double> &Entity::getSize() const {
        return size;
    }

    void Entity::setPosition(const std::pair<double, double> &_position) {
        this->position = _position;
    }

    void Entity::setSize(const std::pair<double, double> &_size) {
        this->size = _size;
    }

    void Entity::setVelocity(const std::pair<double, double> &_velocity) {
        this->velocity = _velocity;
    }

    void Entity::move(const std::pair<double, double> &offset) {
        // Simply add offset to currentPos
        this->position.first += offset.first;
        this->position.second += offset.second;
    }

    void Entity::setOrigin(const std::pair<double, double> &_origin) {
        this->origin = _origin;
    }

    EntityAIState Entity::getCurState() const {
        return curState;
    }

    void Entity::setCurState(EntityAIState _curState) {
        this->curState = _curState;
    }

    bool Entity::isCurrentlyColliding() const {
        return currentlyColliding;
    }

    void Entity::setIsCurrentlyColliding(bool _currentlyColliding) {
        this->currentlyColliding = _currentlyColliding;
    }
}