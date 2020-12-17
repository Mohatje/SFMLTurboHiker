#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "../Parser/ini_configuration.h"
#include "../Logic/PassingHiker1.h"

namespace turbohikerSFML {

    class PassingHiker1 : public turbohiker::PassingHiker1 {
    public:
        PassingHiker1() = default;
        PassingHiker1(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile);

        void display() override;
        void update(float dTime) override;
        void move(const std::pair<double, double>& offset) override;
        bool doTypeSpecificAction() override;

        void init();
        void spawn(double playerY);

        void setPosition(const std::pair<double, double> &_position) override;
        void setSize(const std::pair<double, double> &_size) override;

        void setOrigin(const std::pair<double, double> &_origin) override;
    private:
        std::weak_ptr<sf::RenderWindow> _window;
        static std::unique_ptr<sf::Texture> obstacleTexture;

        std::unique_ptr<sf::RectangleShape> obstacleRect;
        sf::IntRect activeRect;

        sf::IntRect inactiveRect;
    };

}
