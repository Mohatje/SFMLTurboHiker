#include "GameAI.h"
#include "Random.h"
#include <cmath>
#include <algorithm>


namespace turbohiker {
    GameAI GameAI::sharedInstance = GameAI();

    GameAI &GameAI::instantiateAI(std::shared_ptr<World> worldPtr) {
        if (sharedInstance._world.lock() == nullptr) {
            sharedInstance._world = worldPtr;
        }
        return sharedInstance;
    }

    GameAI &GameAI::getInstance() {
        return sharedInstance;
    }

    void GameAI::updateHiker(std::shared_ptr<Entity>& hiker, float dTime) {
        getInstance()._updateHiker(hiker, dTime);
    }

    void GameAI::_updateHiker(std::shared_ptr<Entity>& hiker, float dTime) {
        EntityType hikerType = hiker->getType();
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
        auto toObserve = getEntitiesInSight(hiker);
        if (toObserve.empty()) return;

        auto onePos = hiker->getPosition();

        std::sort(toObserve.begin(), toObserve.end(), [] (std::shared_ptr<Entity> st, std::shared_ptr<Entity> nd) {

            return st->getPosition().second > nd->getPosition().second;
        });

        for (auto& ent : toObserve) {
            if (ent->getType() != EntityType::StaticHikerActive && ent->getType() != EntityType::MovingHikerActive) continue;
            if (ent->getPosition().second > onePos.second) continue;
            avoidObstacle(hiker, ent);
            if (hiker->getCurState() != EntityAIState::Idle) return;
        }

    }

    void GameAI::_updateRacer(std::shared_ptr<Entity>& hiker, float dTime) {
        auto toObserve = getEntitiesInSight(hiker);

        auto onePos = hiker->getPosition();
        auto oneSize = hiker->getSize();
        oneSize.first /= 2.0;
        oneSize.second /= 2.0;

        auto playerPos = _world.lock()->getPlayerPosition();

        std::sort(toObserve.begin(), toObserve.end(), [](std::shared_ptr<Entity> st, std::shared_ptr<Entity> nd) {

            return st->getPosition().second < nd->getPosition().second;
        });

        if (hiker->getCurState() != EntityAIState::Idle) {
            return;
        }

        for (auto &ent : toObserve) {
            if (    !(ent->getType() == EntityType::StaticHikerActive ||
                      ent->getType() == EntityType::MovingHikerActive ||
                      ent->getType() == EntityType::RacingHiker       ||
                      ent->getType() == EntityType::Player) )
                continue;

            if (ent->getPosition().second < onePos.second) continue;
            avoidObstacle(hiker, ent);
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
            if (dX > 0.0) {
                if (onePos.first > 3.0) {
                    hiker->setCurState(EntityAIState::RunL);
                    return;
                }

                hiker->setCurState(EntityAIState::RunR);
                return;
            } else {
                if (onePos.first < -3.0) {
                    hiker->setCurState(EntityAIState::RunR);
                    return;
                }

                hiker->setCurState(EntityAIState::RunL);
                return;
            }
        }
    }
}
