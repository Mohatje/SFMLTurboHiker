#include "EntityFactory.h"
#include "../Logic/HelperFunctions.h"
#include "Player.h"
#include "World.h"


namespace turbohikerSFML {

    EntityFactory::EntityFactory(std::shared_ptr<sf::RenderWindow> _window, const ini::Configuration& _config)
    : window(_window), config(_config) {

    }

    std::unique_ptr<turbohiker::Entity> EntityFactory::createEntity(turbohiker::EntityType ent) {
        std::weak_ptr<sf::RenderWindow> weakPtrWindow = window;
        std::unique_ptr<turbohiker::Entity> entity;;
        switch (ent) {
            case turbohiker::EntityType::Invalid:
                entity = nullptr;
                break;
            case turbohiker::EntityType::Player:
                entity = std::unique_ptr<turbohiker::Entity> (new Player(weakPtrWindow, config));
                break;
            case turbohiker::EntityType::RacingHiker:
                break;
            case turbohiker::EntityType::StaticHiker:
                break;
            case turbohiker::EntityType::MovingHiker:
                break;
            case turbohiker::EntityType::World:
                entity = std::unique_ptr<turbohiker::Entity> (new World(weakPtrWindow, config));
                break;
            case turbohiker::EntityType::Tile:
                break;
        }
        return entity;
    }


}