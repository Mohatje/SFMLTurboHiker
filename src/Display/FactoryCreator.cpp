#include "FactoryCreator.h"
#include "../Logic/HelperFunctions.h"
#include "EntityFactory.h"


namespace turbohikerSFML {

    std::unique_ptr<turbohiker::AbstractFactory>
    FactoryCreator::getFactory(const std::string &factoryName,
                               std::shared_ptr<sf::RenderWindow> &_window,
                               const ini::Configuration &config) {

        if (turbohiker::HelperFunctions::stringCompare(factoryName, "Entity")) {
            return std::unique_ptr<turbohiker::AbstractFactory>(new EntityFactory(_window, config));
        }

        return nullptr;
    }

}
