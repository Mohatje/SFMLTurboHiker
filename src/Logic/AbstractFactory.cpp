#include "AbstractFactory.h"

namespace turbohiker {

    // Empty method, FWIW this whole class can be an interface
    std::unique_ptr<Entity> AbstractFactory::createEntity(EntityType ent) {
        return nullptr;
    }
}