#include "World.h"
//#include <cmath>


namespace turbohiker {

    void World::move(const std::pair<double, double> &offset) {     }

    // Will be using this function for collision control
    void World::doTypeSpecificAction() {
        for (uint32_t i = 0; i < worldEntities.size() - 1; i++) {
            for (uint32_t j = i + 1; j < worldEntities.size() && j != i; j++) {
                checkCollision(*std::next(worldEntities.begin(), i),
                               *std::next(worldEntities.begin(), j));
            }
        }

        for (auto& ent : worldEntities)
            ent->doTypeSpecificAction();
    }

    // AABB collision detecting algo
    bool World::checkCollision(const EntityRef& entOne, const EntityRef& entTwo) {
        auto onePos = entOne->getPosition();
        auto oneSize = entOne->getSize();
        auto twoPos = entTwo->getPosition();
        auto twoSize = entTwo->getSize();

        oneSize.first /= 2.0;
        oneSize.second /= 2.0;
        twoSize.first /= 2.0;
        twoSize.second /= 2.0;

        double dX = onePos.first - twoPos.first;
        double dY = onePos.second - twoPos.second;

        double intersectX = std::abs(dX) - (oneSize.first + twoSize.first);
        double intersectY = std::abs(dY) - (oneSize.second + twoSize.second);


        if (intersectX < 0.0 && intersectY < 0.0) {
            if (std::abs(intersectX) > std::abs(intersectY)) {
                if (dY > 0.0) {
                    entOne->move({0.0, -intersectY * 1.0});
                    entTwo->move({0.0, intersectY * 0.0});
                } else {
                    entOne->move({0.0, intersectY * 1.0});
                    entTwo->move({0.0, -intersectY * 0.0});
                }
            } else {
                if (dX > 0.0) {
                    entOne->move({-intersectX * 1.0, 0.0});
                    entTwo->move({intersectX * 0.0, 0.0});
                } else {
                    entOne->move({intersectX * 1.0, 0.0});
                    entTwo->move({-intersectX * 0.0, 0.0});
                }
            }
            return true;
        }
        return false;

    }

    void World::update(float dt) {
        for (auto& entity : worldEntities) {
            entity->doTypeSpecificAction();
            entity->update(dt);
        }
    }

    void World::display() {
        for (auto& tile : worldTiles)
            tile->display();
        for (auto& entity : worldEntities) {
            entity->display();
        }
    }

    bool World::addEntity(EntityRef ent) {
        return worldEntities.insert(std::move(ent)).second;
    }


    std::set<World::EntityRef>& World::getEntities() {
        return worldEntities;
    }

    bool World::addTile(World::EntityRef tile) {
        return worldTiles.insert(std::move(tile)).second;
    }

    std::set<World::EntityRef> &World::getTiles() {
        return worldTiles;
    }

    std::pair<double, double> World::getPlayerSize() {
        std::pair<double, double> ret { 0.0, 0.0 };
        for (auto& entity : worldEntities) {
            if (entity->getType() == turbohiker::EntityType::Player)
                ret = entity->getSize();
        }
        return ret;
    }

    std::pair<double, double> World::getPlayerPosition() {
        std::pair<double, double> ret { 0.0, 0.0 };
        for (auto& entity : worldEntities) {
            if (entity->getType() == turbohiker::EntityType::Player)
                ret = entity->getPosition();
        }
        return ret;
    }

    std::pair<double, double> World::getPlayerVelocity() {
        std::pair<double, double> ret { 0.0, 0.0 };
        for (auto& entity : worldEntities) {
            if (entity->getType() == turbohiker::EntityType::Player)
                ret = entity->getVelocity();
        }
        return ret;
    }

    float World::getSpeed() const {
        return speed;
    }

    void World::setSpeed(float _speed) {
        speed = _speed;
    }


}