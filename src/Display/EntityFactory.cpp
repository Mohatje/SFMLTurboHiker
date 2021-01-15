#include "EntityFactory.h"
#include "../Logic/HelperFunctions.h"
#include "PassingHiker1.h"
#include "PassingHiker2.h"
#include "Player.h"
#include "RacingHiker.h"
#include "World.h"

namespace turbohikerSFML {

EntityFactory::EntityFactory(std::shared_ptr<sf::RenderWindow> _window, const ini::Configuration& _config)
    : window(_window), config(_config)
{
}

std::unique_ptr<turbohiker::Entity> EntityFactory::createEntity(turbohiker::EntityType ent)
{
        // simple switch case to create every possible entity, sometimes there are duplicates (in the switch statement)
        // which is fine
        std::weak_ptr<sf::RenderWindow> weakPtrWindow = window;
        std::unique_ptr<turbohiker::Entity> entity;
        switch (ent) {
        case turbohiker::EntityType::Invalid:
                entity = nullptr;
                break;
        case turbohiker::EntityType::Player:
                entity = std::unique_ptr<turbohiker::Entity>(new Player(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::RacingHiker:
                entity = std::unique_ptr<turbohiker::Entity>(new RacingHiker(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::StaticHikerActive:
                entity = std::unique_ptr<turbohiker::Entity>(new PassingHiker1(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::StaticHikerInactive:
                entity = std::unique_ptr<turbohiker::Entity>(new PassingHiker1(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::MovingHikerActive:
                entity = std::unique_ptr<turbohiker::Entity>(new PassingHiker2(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::MovingHikerInactive:
                entity = std::unique_ptr<turbohiker::Entity>(new PassingHiker2(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::World:
                entity = std::unique_ptr<turbohiker::Entity>(new World(weakPtrWindow, config));
                break;
        case turbohiker::EntityType::Tile:
                break;
        }
        return entity;
}

} // namespace turbohikerSFML