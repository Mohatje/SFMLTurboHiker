#include "EntityFactory.h"
#include "HelperFunctions.h"
#include "Player.h"
#include "World.h"

namespace turbohiker {
    std::unique_ptr<Entity> EntityFactory::createEntity(EntityType ent) {
        std::unique_ptr<Entity> entity;
        switch (ent) {
            case EntityType::Invalid:
                break;
            case EntityType::Player:
                entity = std::unique_ptr<Entity> (new Player());
                break;
            case EntityType::RacingHiker:
                break;
            case EntityType::StaticHiker:
                break;
            case EntityType::MovingHiker:
                break;
            case EntityType::World:
                entity = std::unique_ptr<Entity> (new World());
                break;
        }
        return entity;
    }
}