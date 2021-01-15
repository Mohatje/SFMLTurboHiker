#pragma once
#include "../Logic/World.h"
#include "../Parser/ini_configuration.h"
#include <SFML/Graphics.hpp>


namespace turbohikerSFML {

    class World : public turbohiker::World {
    public:

        /**
         * Default constructor
         */
        World() = default;

        /**
         * Default destructor
         */
        ~World() override = default;

        /**
         * World constructor
         * @param window        weak pointer to the game window
         * @param configFile    config file from which we load the world's attributes
         */
        World(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration& config);

        /**
         * Method to handle SFML specific events which have effect on the world
         * @param event     sf::Event reference to be handled
         */
        void handleGameEvent(sf::Event &event);
        void update(float dTime) override;

    private:
        sf::Keyboard::Key speedToggle;
        sf::Keyboard::Key yellKey;
        std::weak_ptr<sf::RenderWindow> _window;
    };
}

