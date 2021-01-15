#include "World.h"
#include "PassingHiker1.h"
#include <algorithm>
#include <cmath>
#include <iostream>

namespace turbohiker {

// Obviously world is not movable
void World::move(const std::pair<double, double>& offset) {}

// Will be using this function for collision control
bool World::doTypeSpecificAction()
{

        // Loop through entities, test for collisions, observe collisions, notify observers of said collisions
        for (uint32_t i = 0; i < worldEntities.size() - 1; i++) {
                bool hasCollided = false;
                if (!(worldEntities[i]->getType() == EntityType::Player ||
                      worldEntities[i]->getType() == EntityType::RacingHiker))
                        continue;
                for (uint32_t j = 0; j < worldEntities.size(); j++) {
                        if (i == j)
                                continue;

                        bool collided = checkCollision(worldEntities[i], worldEntities[j]);

                        if (collided && worldEntities[j]->getType() != EntityType::Tile) {
                                hasCollided = true;
                        }
                }

                if (hasCollided && !worldEntities[i]->isCurrentlyColliding()) {
                        worldEntities[i]->notifyObservers(ObservableEvent::Collision);
                }
                worldEntities[i]->setIsCurrentlyColliding(hasCollided);
        }

        // Test for yelling, remove nearest obstacle if someone yelled
        for (auto& ent : worldEntities) {
                if (ent->getType() == EntityType::Player || ent->getType() == EntityType::RacingHiker) {
                        bool entAction = ent->doTypeSpecificAction();
                        if (entAction) {
                                ent->setCurState(EntityAIState::UnYell);
                                if (yelled) {
                                        yelled = false;
                                        removeNearestObstacle(ent->getPosition());
                                }
                        }
                }
        }
        return false;
}

bool World::removeNearestObstacle(const std::pair<double, double>& distPos)
{
        double distance = 1000.0;
        SharedEntityRef closestEnt;

        // Loop through entities and get the closest entity
        // If two entities are just as close to the yelling entity then the latest one in the vector gets chosen
        for (auto& ent : getEntities()) {
                auto entType = ent->getType();
                if (entType == turbohiker::EntityType::StaticHikerActive ||
                    entType == turbohiker::EntityType::MovingHikerActive) {
                        auto entPos = ent->getPosition();
                        if (entPos.second < distPos.second) {
                                continue;
                        }

                        double tmpDistance =
                            sqrt(pow((distPos.first - entPos.first), 2) + pow((distPos.second - entPos.second), 2));
                        closestEnt = distance > tmpDistance ? ent : closestEnt;
                        distance = distance > tmpDistance ? tmpDistance : distance;
                }
        }

        if (distance > 15)
                return false;

        if (closestEnt->getType() == turbohiker::EntityType::StaticHikerActive) {
                // Using raw pointer here for a bit, shouldn't pose any memory problem though
                // Since the raw pointer is single use only thing anyways.
                // The deletion will still happen as per unique ptr instruction
                // Not too worried about its performance implications because this isn't called very often.
                dynamic_cast<PassingHiker1*>(closestEnt.get())->setActive(false);
        } else {
                closestEnt->setCurState(turbohiker::EntityAIState::SlowDown);
        }
        return true;
}

double World::getCollisionForce(EntityType typeOne, EntityType typeTwo)
{
        // For each collision type we need a resolution force,
        // this real number tells us what should move what,
        // for example an entity cannot move a barrier or an obstacle shouldn't collide with a barrier etc
        // Returning -1.0 for no collision control
        if (typeOne == EntityType::RacingHiker && typeTwo == EntityType::RacingHiker)
                return 0.5;

        // Two static obstacles
        if (typeOne == EntityType::StaticHikerActive && typeTwo == EntityType::StaticHikerActive)
                return -1.0;

        // Two tiles
        if (typeOne == typeTwo && typeOne == EntityType::Tile)
                return -1.0;

        // One or more Inactive obstacles
        if (typeOne == EntityType::StaticHikerInactive || typeTwo == EntityType::StaticHikerInactive)
                return -1.0;

        // Collider vs static obstacle
        if ((typeOne == EntityType::StaticHikerActive && typeTwo == EntityType::Tile) ||
            (typeTwo == EntityType::StaticHikerActive && typeOne == EntityType::Tile)) {
                return -1.0;
        }

        // Moving obstacle vs collider
        if ((typeOne == EntityType::MovingHikerActive && typeTwo == EntityType::Tile) ||
            (typeTwo == EntityType::MovingHikerActive && typeOne == EntityType::Tile)) {
                return -1.0;
        }
        if (typeOne == EntityType::StaticHikerActive)
                return 1.0;
        if (typeOne == EntityType::MovingHikerActive && typeTwo == EntityType::MovingHikerActive)
                return 1.0;

        // First entity is collider => push everything
        if (typeOne == EntityType::Tile)
                return 1.0;

        // First entity is moving hiker, push the rest by .25
        if (typeOne == EntityType::MovingHikerActive)
                return 0.60;
        if (typeTwo == EntityType::MovingHikerActive)
                return 0.40;
        if (typeOne == EntityType::Player && typeTwo == EntityType::RacingHiker)
                return 0.5;
        if (typeOne == EntityType::RacingHiker && typeTwo == EntityType::Player)
                return 0.5;

        return 0.0;
}

// AABB collision detecting algo
bool World::checkCollision(const SharedEntityRef& entOne, const SharedEntityRef& entTwo)
{
        double collisionForce = getCollisionForce(entOne->getType(), entTwo->getType());
        if (entOne->getType() == EntityType::StaticHikerActive && entTwo->getType() == EntityType::Player) {
                std::cerr << collisionForce << std::endl;
        }
        if (collisionForce < 0.0)
                return false;

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

        // there is a collision - intersecting both x and y
        if (intersectX < 0.0 && intersectY < 0.0) {
                // Push the objects out of each other on the smallest intersect (smaller jump)
                if (std::abs(intersectX) > std::abs(intersectY)) {
                        // Positive delta => entOne is under entTwo
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

void World::update(float dt)
{
        for (auto& entity : worldEntities) {
                entity->doTypeSpecificAction();
                entity->update(dt);
        }
}

void World::display()
{
        // Display layers: map tiles -> inactive obstacles -> the rest
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

void World::displayTiles()
{
        for (auto& tile : worldTiles)
                tile->display();
}

void World::displayEntities()
{
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

void World::addEntity(EntityRef ent)
{
        if (ent->getType() == EntityType::Player) {
                player = std::move(ent);
                worldEntities.push_back(player);
        } else {
                worldEntities.push_back(std::move(ent));
        }
}

std::vector<World::SharedEntityRef>& World::getEntities() { return worldEntities; }

void World::addTile(EntityRef tile) { worldTiles.push_back(std::move(tile)); }

std::vector<World::SharedEntityRef>& World::getTiles() { return worldTiles; }

std::pair<double, double> World::getPlayerSize() { return getPlayerPtr()->getSize(); }

std::pair<double, double> World::getPlayerPosition() { return getPlayerPtr()->getPosition(); }

std::pair<double, double> World::getPlayerVelocity() { return getPlayerPtr()->getVelocity(); }

const World::SharedEntityRef& World::getPlayerPtr() { return player; }

float World::getSpeed() const { return speed; }

void World::setSpeed(float _speed) { speed = _speed; }

bool World::hasYelled() const { return yelled; }

void World::setYelled(bool _yelled) { yelled = _yelled; }

void World::removeObstacles(double bottomY)
{
        // Cleans up everything below the give y value
        // Game view scrolls up, and to avoid making thousands of tile entities the older ones get removed
        for (int i = 0; i < worldEntities.size();) {
                if (worldEntities[i]->getPosition().second < bottomY) {
                        worldEntities[i].reset();
                        worldEntities.erase(worldEntities.begin() + i);
                } else {
                        i++;
                }
        }
        for (int i = 0; i < worldTiles.size();) {
                if (worldTiles[i]->getPosition().second < bottomY) {
                        worldTiles[i].reset();
                        worldTiles.erase(worldTiles.begin() + i);
                } else {
                        i++;
                }
        }
}

void World::clearEntitiesAbove(double yConstraint)
{
        for (int i = 0; i < worldEntities.size();) {
                if (worldEntities[i]->getPosition().second > yConstraint) {
                        worldEntities[i].reset();
                        worldEntities.erase(worldEntities.begin() + i);
                } else {
                        i++;
                }
        }
}

bool World::checkForFinish(double finishLine)
{
        // Making use of a static counter and vector to put the players in the order they finished in
        static int playersFinished = 0;
        static auto vec = worldEntities;

        for (auto it = vec.begin(); it != vec.end();) {
                auto ent = *it;
                if (!(ent->getType() == EntityType::RacingHiker || ent->getType() == EntityType::Player)) {
                        ++it;
                        continue;
                }
                auto entPos = ent->getPosition();

                if (entPos.second >= finishLine) {
                        playersFinished++;
                        ent->notifyObservers(static_cast<ObservableEvent>(playersFinished));
                        ent->setCurState(EntityAIState::Finished);
                        ent->move({0, 1.5});
                        worldEntities.erase(std::find(worldEntities.begin(), worldEntities.end(), ent));
                        vec.erase(it);
                } else {
                        ++it;
                }
        }
        return playersFinished == 6;
}

void World::observeOrder()
{
        // Observers the current order of the entities, same principle as the checkForFinish method
        // The first couple of players in the lead get more points if they hold that position
        if (speed >= 500.f && player->getCurState() != EntityAIState::Finished) {
                player->notifyObservers(ObservableEvent::WorldSpeed);
        }

        std::vector<SharedEntityRef> vec;
        for (auto& ent : worldEntities) {
                if (ent->getType() == EntityType::Player || ent->getType() == EntityType::RacingHiker)
                        vec.push_back(ent);
        }
        std::sort(vec.begin(), vec.end(), [](SharedEntityRef st, SharedEntityRef nd) {
                return st->getPosition().second > nd->getPosition().second;
        });
        int i = 10;
        for (auto& ent : vec) {
                if (ent->getCurState() != EntityAIState::Finished) {
                        ent->notifyObservers(static_cast<ObservableEvent>(i));
                }
                i++;
        }
}
} // namespace turbohiker