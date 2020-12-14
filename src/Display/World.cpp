#include "World.h"
#include "KeyConfigHelper.h"
#include "Transformation.h"


namespace turbohikerSFML {

    World::World(const std::weak_ptr<sf::RenderWindow> &window,
                 const ini::Configuration &config) : _window(window) {
        std::string speedKey = config["Controls"]["SpeedToggle"].as_string_or_default("F");
        speedToggle = KeyConfigHelper::keyboardFromString(speedKey);
    }

    void World::update(float dt) {


//        while ( _window.lock()->pollEvent(worldEvent) ) {
//            if (worldEvent.type == sf::Event::KeyReleased && worldEvent.key.code == speedToggle) {
//                setSpeed(getSpeed() + 5.0f);
//                if (getSpeed() >= 15) setSpeed(0.0f);
//            }
//        }



        float offset = Transformation::convertSizeFromPixels(*_window.lock(), {0.0, getSpeed()}).second;
        auto& entities = getEntities();
        for (auto& entity : entities) {
            entity->doTypeSpecificAction();
            entity->update(dt);
            if (entity->getType() == turbohiker::EntityType::Player) {
                entity->move({0, offset * 0.85});
            }
            else {
                entity->move({0, offset});
            }
        }
    }
}

