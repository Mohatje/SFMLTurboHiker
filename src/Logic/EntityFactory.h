#pragma once
#include "AbstractFactory.h"

namespace turbohiker {
    class EntityFactory : public AbstractFactory {
    public:


		std::unique_ptr<Entity> createEntity(EntityType ent) override;
    };
}
