#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "../Parser/ini_configuration.h"
#include "../Logic/PassingHiker2.h"

namespace turbohikerSFML {

    class PassingHiker2 : public turbohiker::PassingHiker2 {
    public:
        PassingHiker2() = default;
        PassingHiker2(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile);

        void display() override;
        void update(float dTime) override;
        void move(const std::pair<double, double> &offset) override;
        bool doTypeSpecificAction() override;

        void init();

        void setPosition(const std::pair<double, double> &_position) override;
        void setSize(const std::pair<double, double> &_size) override;
        void setOrigin(const std::pair<double, double> &_origin) override;

    private:
        std::weak_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::Texture> obstacleTexture;
        std::unique_ptr<sf::RectangleShape> obstacleRect;
        std::unique_ptr<Animation> anim;

        int runAnimation;
    };

}