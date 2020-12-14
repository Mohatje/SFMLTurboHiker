#include "AbstractFactory.h"
#include <string>

namespace turbohiker {
    std::unique_ptr<Entity> AbstractFactory::createEntity(EntityType ent) {
        return nullptr;
    }
}