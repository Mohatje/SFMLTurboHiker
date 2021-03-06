#pragma once
#include "../Logic/PassingHiker1.h"
#include "../Parser/ini_configuration.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace turbohikerSFML {

class PassingHiker1 : public turbohiker::PassingHiker1
{
public:
        /**
         * Default Constructor
         */
        PassingHiker1() = default;

        /**
         * Static Hiker constructor
         * @param window weak pointer to the game window
         * @param configFile config file from which we load the hiker's attributes
         */
        PassingHiker1(const std::weak_ptr<sf::RenderWindow>& window, const ini::Configuration& configFile);

        void display() override;
        void update(float dTime) override;
        void move(const std::pair<double, double>& offset) override;
        bool doTypeSpecificAction() override;

        /**
         * Method to initialize the Static Hiker
         */
        void init();

        /**
         * Method to spawn this hiker around the player, with a bit of randomness
         * @param playerY current Y position of the player
         */
        void spawn(double playerY);

        void setPosition(const std::pair<double, double>& _position) override;
        void setSize(const std::pair<double, double>& _size) override;

        void setOrigin(const std::pair<double, double>& _origin) override;
        void setActive(bool _active) override;

private:
        std::weak_ptr<sf::RenderWindow> _window;
        static std::unique_ptr<sf::Texture> obstacleTexture;

        std::unique_ptr<sf::RectangleShape> obstacleRect;
        sf::IntRect activeRect;

        sf::IntRect inactiveRect;
};

} // namespace turbohikerSFML
