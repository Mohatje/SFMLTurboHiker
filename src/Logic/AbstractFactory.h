#pragma once
#include "Entity.h"
#include <memory>

namespace turbohiker {
    class AbstractFactory {
    public:
        virtual std::unique_ptr<Entity> createEntity(EntityType ent);
    };

}