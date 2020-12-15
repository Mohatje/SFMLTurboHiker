#include "World.h"
#include "KeyConfigHelper.h"
#include "Transformation.h"


namespace turbohikerSFML {

    World::World(const std::weak_ptr<sf::RenderWindow> &window,
                 const ini::Configuration &config) : _window(window) {
        std::string speedKey = config["Controls"]["SpeedToggle"].as_string_or_default("F");
        speedToggle = KeyConfigHelper::keyboardFromString(speedKey);
    }

    void World::handleGameEvent(sf::Event& event) {
        if (event.type == sf::Event::KeyReleased && event.key.code == speedToggle) {
            setSpeed(getSpeed() + 300.0f);
            if (getSpeed() >= 650.0f) setSpeed(0.0f);
        }
    }

    void World::update(float dt) {

        float offset = Transformation::convertSizeFromPixels(*_window.lock(), {0.0, getSpeed()}).second;
        auto& entities = getEntities();
        for (auto& entity : entities) {
            if (entity->getType() == turbohiker::EntityType::Player) {
                entity->move({0, offset * 0.85 * dt});
                std::cout << entity->getPosition().first << "\t" << entity->getPosition().second << std::endl;
            }
            else {
                entity->move({0, offset * dt});
            }
            entity->doTypeSpecificAction();
            entity->update(dt);
        }

    }


}

