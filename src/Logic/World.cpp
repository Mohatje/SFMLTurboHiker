#include "World.h"
#include <iostream>
#include <cmath>


namespace turbohiker {

    void World::move(const std::pair<double, double> &offset) {     }

    // Will be using this function for collision control
    bool World::doTypeSpecificAction() {
        for (uint32_t i = 0; i < worldEntities.size() - 1; i++) {
            for (uint32_t j = i + 1; j < worldEntities.size(); j++) {
                checkCollision(*std::next(worldEntities.begin(), i),
                               *std::next(worldEntities.begin(), j));
            }
        }

        for (auto& ent : worldEntities) {
            bool entAction = ent->doTypeSpecificAction();
            if (ent->getType() == EntityType::Player && entAction && hasYelled()) {
                yelled = false;
                removeNearestObstacle();
            }
        }
        return false;
    }

    bool World::removeNearestObstacle() {
        return false;
    }

    double World::getCollisionForce(EntityType typeOne, EntityType typeTwo) {

        // Two static obstacles
        if (typeOne == EntityType::StaticHikerActive && typeTwo == EntityType::StaticHikerActive) return -1.0;

        // Two tiles
        if (typeOne == typeTwo && typeOne == EntityType::Tile) return -1.0;

        // One or more Inactive obstacles
        if (typeOne == EntityType::StaticHikerInactive || typeTwo == EntityType::StaticHikerInactive) return -1.0;

        // Collider vs static obstacle
        if ((typeOne == EntityType::StaticHikerActive && typeTwo == EntityType::Tile)
            || (typeTwo == EntityType::StaticHikerActive && typeOne == EntityType::Tile)) {
            return -1.0;
        }


        // Moving obstacle vs collider
        if ((typeOne == EntityType::MovingHikerActive && typeTwo == EntityType::Tile)
            || (typeTwo == EntityType::MovingHikerActive && typeOne == EntityType::Tile)) {
            return -1.0;
        }

        // First entity is collider => push everything
        if (typeOne == EntityType::Tile) return 1.0;

        if (typeTwo == EntityType::MovingHikerActive) return 0.75;
        if (typeOne == EntityType::MovingHikerActive) return 0.25;

        return 0.0;
    }

    // AABB collision detecting algo
    bool World::checkCollision(const EntityRef& entOne, const EntityRef& entTwo) {
        double collisionForce = getCollisionForce(entOne->getType(), entTwo->getType());
        if (collisionForce < 0.0) return false;

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
                    entOne->move({0.0, -intersectY * (1.0 - collisionForce)});
                    entTwo->move({0.0, intersectY * collisionForce});
                } else {
                    entOne->move({0.0, intersectY * (1.0 - collisionForce)});
                    entTwo->move({0.0, -intersectY * collisionForce});
                }
            } else {
                if (dX > 0.0) {
                    entOne->move({-intersectX * (1.0 - collisionForce), 0.0});
                    entTwo->move({intersectX * collisionForce, 0.0});
                } else {
                    entOne->move({intersectX * (1.0 - collisionForce), 0.0});
                    entTwo->move({-intersectX * collisionForce, 0.0});
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
            if (entity->getType() == EntityType::StaticHikerInactive) {
                entity->display();
            }
        }
        for (auto& entity : worldEntities) {
            if (entity->getType() != EntityType::StaticHikerInactive) {
                entity->display();
            }
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
        return getPlayerPtr()->getSize();
    }

    std::pair<double, double> World::getPlayerPosition() {
        return getPlayerPtr()->getPosition();
    }

    std::pair<double, double> World::getPlayerVelocity() {
        return getPlayerPtr()->getVelocity();
    }

    void World::movePlayer(const std::pair<double, double>& offset) {
        for (auto& entity : worldEntities) {
            if (entity->getType() == turbohiker::EntityType::Player)
                entity->move(offset);
        }
    }

    const std::unique_ptr<Entity>& World::getPlayerPtr() {
        static const EntityRef null ( nullptr );
        for (auto& entity : worldEntities) {
            if (entity->getType() == turbohiker::EntityType::Player)
                return entity;
        }
        return null;
    }

    float World::getSpeed() const {
        return speed;
    }

    void World::setSpeed(float _speed) {
        speed = _speed;
    }

    bool World::hasYelled() const {
        return yelled;
    }

    void World::setYelled(bool _yelled) {
       yelled = _yelled;
    }

    void World::removeObstacles(double bottomY) {
        std::set<EntityRef>::iterator it;
        for (it = worldEntities.begin(); it != worldEntities.end(); it++) {
            if ((*it)->getPosition().second < bottomY) {
                worldEntities.erase(it);
            }
        }
        for (it = worldTiles.begin(); it != worldTiles.end(); it++) {
            if ((*it)->getPosition().second < bottomY) {
                worldTiles.erase(it);
            }
        }
    }


}