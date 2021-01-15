#pragma once
#include "../Logic/PassingHiker2.h"
#include "../Parser/ini_configuration.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace turbohikerSFML {

class PassingHiker2 : public turbohiker::PassingHiker2
{
public:
        /**
         * Default constructor
         */
        PassingHiker2() = default;

        /**
         * Moving Hiker constructor
         * @param window weak pointer to the game window
         * @param configFile config file from which we load the hiker's attributes
         */
        PassingHiker2(const std::weak_ptr<sf::RenderWindow>& window, const ini::Configuration& configFile);

        void display() override;
        void update(float dTime) override;
        void move(const std::pair<double, double>& offset) override;
        bool doTypeSpecificAction() override;

        /**
         * Method to initialize the Moving Hiker
         */
        void init();

        void setPosition(const std::pair<double, double>& _position) override;
        void setSize(const std::pair<double, double>& _size) override;
        void setOrigin(const std::pair<double, double>& _origin) override;

private:
        std::weak_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::Texture> obstacleTexture;
        std::unique_ptr<sf::RectangleShape> obstacleRect;
        std::unique_ptr<Animation> anim;

        int runAnimation;
};

} // namespace turbohikerSFML