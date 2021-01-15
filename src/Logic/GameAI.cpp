#include "GameAI.h"
#include "Random.h"
#include <cmath>
#include <algorithm>


namespace turbohiker {
    GameAI GameAI::sharedInstance = GameAI();

    GameAI &GameAI::instantiateAI(std::shared_ptr<World> worldPtr) {
        // instantiation of the world pointer, if it's null then that means it's the first time we ran instantiateAI
        if (sharedInstance._world.lock() == nullptr) {
            sharedInstance._world = worldPtr;
        }
        return sharedInstance;
    }

    GameAI &GameAI::getInstance() {
        return sharedInstance;
    }

    void GameAI::updateHiker(std::shared_ptr<Entity>& hiker, float dTime) {
        // Static redirect which saves met from repetitive getInstance() calls, since those can be abstracted away
        getInstance()._updateHiker(hiker, dTime);
    }

    void GameAI::_updateHiker(std::shared_ptr<Entity>& hiker, float dTime) {
        EntityType hikerType = hiker->getType();

        // Determine type of hiker, AI is only applied on Moving Hikers/obstacles and other competitors
        if (hikerType == EntityType::MovingHikerActive) {
            _updateMovingHiker(hiker, dTime);
        } else if (hikerType == EntityType::RacingHiker) {
            _updateRacer(hiker, dTime);
        }

    }

    std::vector<std::shared_ptr<Entity>> GameAI::getEntitiesInSight(std::shared_ptr<Entity>& hiker) {
        std::vector<std::shared_ptr<Entity>> ret;
        auto curPosition = hiker->getPosition();
        auto xConstraint = std::abs(curPosition.first) + 2.0;
        auto yConstraint = std::abs(curPosition.second) + 2.0;

        // Loop through all entities and get their distance to our entity
        // If that distance is lower than 2 world coordinate units then this means they are in sight of the entity
        for (auto& entity : _world.lock()->getEntities()) {
            if (entity == hiker) continue;
            auto entPos = entity->getPosition();

            double tmpDistance = sqrt( pow((curPosition.first - entPos.first), 2) + pow((curPosition.second - entPos.second), 2) );

            if (std::abs(tmpDistance) < 2.0)
                ret.push_back(entity);

        }
        return ret;
    }


    void GameAI::_updateMovingHiker(std::shared_ptr<Entity>& hiker, float dTime) {
        // Get entities in sight of the hiker,
        // return if obstacle has no one in sight (hiker just keeps going at current rate)
        auto toObserve = getEntitiesInSight(hiker);
        if (toObserve.empty()) return;

        auto onePos = hiker->getPosition();

        // Use of lambda function to sort all the entities based on y value
        // (closest entities/obstacles to obstacle are first in vector)
        std::sort(toObserve.begin(), toObserve.end(), [] (std::shared_ptr<Entity> st, std::shared_ptr<Entity> nd) {
            return st->getPosition().second > nd->getPosition().second;
        });

        // Decide whether we should avoid the obstacle or not. (based on type and y position)
        for (auto& ent : toObserve) {
            if (ent->getType() != EntityType::StaticHikerActive && ent->getType() != EntityType::MovingHikerActive) continue;
            if (ent->getPosition().second > onePos.second) continue;
            avoidObstacle(hiker, ent);
            if (hiker->getCurState() != EntityAIState::Idle) return;
        }

    }

    void GameAI::_updateRacer(std::shared_ptr<Entity>& hiker, float dTime) {
        // Get entities in sight of the hiker,
        // return if obstacle has no one in sight (hiker just keeps going at current rate)
        auto toObserve = getEntitiesInSight(hiker);

        auto onePos = hiker->getPosition();

        // player position, used to modify the chance of speeding up
        auto playerPos = _world.lock()->getPlayerPosition();

        // Use of lambda function to sort all the entities based on y value
        // (closest entities/obstacles to obstacle are first in vector)
        std::sort(toObserve.begin(), toObserve.end(), [](std::shared_ptr<Entity> st, std::shared_ptr<Entity> nd) {

            return st->getPosition().second < nd->getPosition().second;
        });

        if (hiker->getCurState() != EntityAIState::Idle) {
            return;
        }

        // Loop through all entities that are observable by the entity (within a range of 2 units)
        for (auto &ent : toObserve) {

            // Excluding Tiles and colliders, those should not be avoided.
            if (    !(ent->getType() == EntityType::StaticHikerActive ||
                      ent->getType() == EntityType::MovingHikerActive ||
                      ent->getType() == EntityType::RacingHiker       ||
                      ent->getType() == EntityType::Player) )
                continue;

            // Go to the next observable entity if the current one is already behind
            if (ent->getPosition().second < onePos.second) continue;

            // Attempt to avoid said obstacle / entity
            avoidObstacle(hiker, ent);

            // Means avoidance was successful
            // Now with a chance of 1% the AI controlled entity (competitor) can attempt to yell at the obstacle
            if (hiker->getCurState() != EntityAIState::Idle) {
                if (ent->getType() == EntityType::MovingHikerActive || ent->getType() == EntityType::RacingHiker) return;
                auto rnd = Random::randFloat(0.f, 1.f);
                if (rnd < 0.01f) {
                    hiker->notifyObservers(ObservableEvent::Yelled);
                    _world.lock()->setYelled(true);
                    hiker->setCurState(EntityAIState::Yell);
                }
                return;
            }
        }

        // The loop is done and we didn't return, so the entity still hasn't done anything
        // So we calculate whether the entity should speed up or slow down
        // This makes the competitors feel alive since their movement isn't set in stone.

        // However this little algorithm tries to keep the entities from straying too far from the player
        // Chance of speeding up goes down the farther ahead the competitor is
        // Chance of slowing down is analogous to speeding up.
        float chanceSpeedup;
        float distanceToPlayer = playerPos.second - hiker->getPosition().second;
        float chance = std::min( ((30.f / 4.f) * std::abs(distanceToPlayer)) + 0.3f, 1.f);
        chanceSpeedup = distanceToPlayer < 0.f ? 1.0f - chance : chance;
        if (std::abs(distanceToPlayer) < 1.5) chanceSpeedup = 0.5;

        auto rnd = Random::randFloat(0.f, 1.f);
        if (rnd < chanceSpeedup) {
            hiker->setCurState(EntityAIState::SpeedUp);
        } else {
            hiker->setCurState(EntityAIState::SlowDown);
        }
    }

    void GameAI::avoidObstacle(std::shared_ptr<Entity>& hiker, std::shared_ptr<Entity>& ent) {

        // Simple method that checks whether the entities intersect on X
        // When an X intersect is detected the hiker tries to avoid the other entity by going to the left or right

        // This method is rather simplistic, while it works `well enough` TM, it still has some weird behaviour

        auto onePos = hiker->getPosition();
        auto oneSize = hiker->getSize();
        oneSize.first /= 2.0;
        oneSize.second /= 2.0;

        auto twoPos = ent->getPosition();
        auto twoSize = ent->getSize();

        twoSize.first /= 2.0;
        twoSize.second /= 2.0;

        double dX = onePos.first - twoPos.first;
        double dY = onePos.second - twoPos.second;
        double intersectX = std::abs(dX) - (oneSize.first + twoSize.first);
        if (intersectX < 0.0) {

            // hiker is to the right of the obstacle / entity
            if (dX > 0.0) {

                // hiker cannot go to the right (collider)
                if (onePos.first >= 3.5) {
                    hiker->setCurState(EntityAIState::RunL);
                    return;
                }

                hiker->setCurState(EntityAIState::RunR);
                return;
            } else {
                if (onePos.first <= -3.45) {
                    hiker->setCurState(EntityAIState::RunR);
                    return;
                }

                hiker->setCurState(EntityAIState::RunL);
                return;
            }
        }
    }
}
