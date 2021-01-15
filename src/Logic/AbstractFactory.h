#pragma once
#include "Entity.h"
#include <memory>

namespace turbohiker {
class AbstractFactory
{
public:
        /**
         * Virtual factory function that returns an entity
         * @param ent EntityType you wish to create
         * @return unique pointer to a newly created entity of type ent
         */
        virtual std::unique_ptr<Entity> createEntity(EntityType ent);
};

} // namespace turbohiker