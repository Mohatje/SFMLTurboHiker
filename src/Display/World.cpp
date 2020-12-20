#include "World.h"
#include "KeyConfigHelper.h"
#include "Transformation.h"
#include "PassingHiker1.h"
#include "../Logic/Random.h"
#include "../Logic/GameAI.h"
#include <cmath>


namespace turbohikerSFML {

    World::World(const std::weak_ptr<sf::RenderWindow> &window,
                 const ini::Configuration &config) : _window(window) {
        std::string speedKey = config["Controls"]["SpeedToggle"].as_string_or_default("F");
        speedToggle = KeyConfigHelper::keyboardFromString(speedKey);

        std::string yellKeyString = config["Controls"]["Yell"].as_string_or_default("Y");
        yellKey = KeyConfigHelper::keyboardFromString(yellKeyString);
        setSpeed(300.0f);
    }

    void World::handleGameEvent(sf::Event& event) {
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == speedToggle) {
                setSpeed(getSpeed() + 300.0f);
//                if (getSpeed() >= 650.0f) setSpeed(300.0f);
                if (getSpeed() >= 450.0f) setSpeed(0.0f);
            }
            else if (event.key.code == yellKey) {
                float rnd = turbohiker::Random::randFloat(0.f, 1.f);
                setYelled( rnd < 0.5f);
            }
        }
    }

    void World::update(float dt) {

        float offset = Transformation::convertSizeFromPixels(*_window.lock(), {0.0, getSpeed()}).second;
        auto& entities = getEntities();
        for (auto& entity : entities) {
            if (entity->getType() == turbohiker::EntityType::Player) {
                entity->move( {0, offset * 0.85 * dt} );
            } else if (entity->getType() == turbohiker::EntityType::MovingHikerActive) {
                turbohiker::GameAI::updateHiker(entity, dt);
            } else if (entity->getType() == turbohiker::EntityType::RacingHiker) {
                entity->move( {0, offset * 0.85 * dt} );
                turbohiker::GameAI::updateHiker(entity, dt);
            } else {
                entity->move( {0, offset * dt} );
            }
            entity->update(dt);
        }

    }

    bool World::removeNearestObstacle(const std::pair<double, double> &distPos) {
        double distance = 1000.0;
        for (auto& ent : getEntities()) {
            if (ent->getType() == turbohiker::EntityType::StaticHikerActive) {
                auto entPos = ent->getPosition();
                if (entPos.second < distPos.second) {
                    continue;
                }

                double tmpDistance = sqrt(pow((distPos.first - entPos.first), 2) + pow((distPos.second - entPos.second), 2) );
                distance = distance > tmpDistance ? tmpDistance : distance;
            }
        }

        if (distance > 15) return false;

        for (auto& ent : getEntities()) {
            if (ent->getType() == turbohiker::EntityType::StaticHikerActive) {
                auto entPos = ent->getPosition();
                if (entPos.second < distPos.second ) continue;

                double tmpDistance = sqrt( pow((distPos.first - entPos.first), 2) + pow((distPos.second - entPos.second), 2) );
                if (tmpDistance == distance) {
                    // Using raw pointer here for a bit, shouldn't pose any memory problem though
                    // Since the raw pointer is single use only thing anyways. The deletion will still happen as per unique ptr instruction
                    dynamic_cast<PassingHiker1*> (ent.get())->setActive(false);
                    return true;
                }
            }
        }

        return false;
    }


}

