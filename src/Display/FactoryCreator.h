#pragma once
#include <SFML/Graphics.hpp>
#include "../Logic/AbstractFactory.h"
#include "../Parser/ini_configuration.h"


namespace turbohikerSFML {

    class FactoryCreator {
    public:
        /**
         * Concrete factory getter
         * @param factoryName factory name (case insensitive
         * @param _window game window
         * @param config config file
         * @return unique AbstractFactory pointer
         */
        static std::unique_ptr<turbohiker::AbstractFactory> getFactory(const std::string &factoryName,
                                                                       std::shared_ptr<sf::RenderWindow> &_window,
                                                                       const ini::Configuration &config);

    public:
        FactoryCreator() = delete;
        FactoryCreator(const FactoryCreator& cpy) = delete;
        ~FactoryCreator() = delete;
    };

}

