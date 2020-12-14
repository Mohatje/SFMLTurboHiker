#include "FactoryCreator.h"
#include "EntityFactory.h"
#include "HelperFunctions.h"

namespace turbohiker {
    std::unique_ptr<AbstractFactory> FactoryCreator::getFactory(const std::string &factoryName) {
        if ( HelperFunctions::stringCompare(factoryName, "entity") ) {
            std::unique_ptr<AbstractFactory> entityFactory(new EntityFactory());
            return entityFactory;
        }

        return std::unique_ptr<AbstractFactory>(nullptr);
    }


}