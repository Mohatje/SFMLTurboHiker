#pragma once
#include "../Logic/World.h"
#include "../Parser/ini_configuration.h"
#include <SFML/Graphics.hpp>


namespace turbohikerSFML {

    class World : public turbohiker::World {
    public:
        World() = default;
        ~World() = default;
        World(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration& config);

        void update(float dTime) override;
        void handleGameEvent(sf::Event &event);
        bool removeNearestObstacle() override;

    private:
        sf::Keyboard::Key speedToggle;
        sf::Keyboard::Key yellKey;

        std::weak_ptr<sf::RenderWindow> _window;

        sf::Event worldEvent {};

    };
}

