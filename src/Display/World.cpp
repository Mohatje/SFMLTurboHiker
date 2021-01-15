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
        // Load yell and speed modify key and set base speed
        std::string speedKey = config["Controls"]["SpeedToggle"].as_string_or_default("F");
        speedToggle = KeyConfigHelper::keyboardFromString(speedKey);

        std::string yellKeyString = config["Controls"]["Yell"].as_string_or_default("Y");
        yellKey = KeyConfigHelper::keyboardFromString(yellKeyString);
        setSpeed(300.0f);
    }

    void World::handleGameEvent(sf::Event& event) {
        // Handle sfml event, used to toggle speed & yelling
        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == speedToggle) {
                setSpeed(getSpeed() + 300.0f);
                if (getSpeed() >= 650.0f) setSpeed(300.0f);
//                if (getSpeed() >= 450.0f) setSpeed(0.0f);
            }
            else if (event.key.code == yellKey) {
                float rnd = turbohiker::Random::randFloat(0.f, 1.f);
                setYelled( rnd < 0.5f);
                getPlayerPtr()->notifyObservers(turbohiker::ObservableEvent::Yelled);
            }
        }
    }

    void World::update(float dt) {
        // Move the entities with the view, except the player and racing hikers those `lag` behind a bit
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


}

