#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "../Parser/ini_configuration.h"
#include "../Logic/Player.h"


namespace turbohikerSFML {
    class Player : public turbohiker::Player {
    public:
        Player() = default;
        Player(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile);

        void display() override;
        void update(float dTime) override;
        void move(const std::pair<double, double>& offset) override;

        void setPosition(const std::pair<double, double> &_position) override;
        void setVelocity(const std::pair<double, double> &_velocity) override;
        void setSize(const std::pair<double, double> &_size) override;

    private:
        std::weak_ptr<sf::RenderWindow> _window;
        std::unique_ptr<Animation> anim;
        std::shared_ptr<sf::Texture> playerTexture;
        std::unique_ptr<sf::RectangleShape> playerRect;
        bool textureFlipped = false;
        
        int idleAnimation;
        int runAnimation;

        sf::Keyboard::Key Left;
        sf::Keyboard::Key Right;
        sf::Keyboard::Key Up;
        sf::Keyboard::Key Down;
        sf::Keyboard::Key Yell;
    };
}
