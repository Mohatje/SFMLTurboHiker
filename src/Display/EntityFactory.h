#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Logic/AbstractFactory.h"
#include "../Parser/ini_configuration.h"


namespace turbohikerSFML {

    class EntityFactory : public turbohiker::AbstractFactory {
    public:
        /**
         * Constructor for the concrete Entity Factory
         * @param _window game window pointer
         * @param config config object pointer
         */
        EntityFactory(std::shared_ptr<sf::RenderWindow> _window, const ini::Configuration& config);

        std::unique_ptr<turbohiker::Entity> createEntity(turbohiker::EntityType) final;
    private:
        std::shared_ptr<sf::RenderWindow> window;
        const ini::Configuration &config;
    };

}

