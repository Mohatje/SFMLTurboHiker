#include "EntityFactory.h"
#include "PassingHiker1.h"
#include "PassingHiker2.h"
#include "HelperFunctions.h"
#include "Player.h"
#include "RacingHiker.h"
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
                entity = std::unique_ptr<Entity> (new RacingHiker());
                break;
            case EntityType::StaticHikerActive:
                entity = std::unique_ptr<Entity> (new PassingHiker1());
                break;
            case EntityType::StaticHikerInactive:
                entity = std::unique_ptr<Entity> (new PassingHiker1());
                break;
            case EntityType::MovingHikerActive:
                entity = std::unique_ptr<Entity> (new PassingHiker2());
                break;
            case EntityType::MovingHikerInactive:
                entity = std::unique_ptr<Entity> (new PassingHiker2());
                break;
            case EntityType::World:
                entity = std::unique_ptr<Entity> (new World());
                break;
        }
        return entity;
    }
}