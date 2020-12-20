#pragma once
#include "../Logic/RacingHiker.h"
#include "Animation.h"
#include "../Parser/ini_configuration.h"
#include <memory>
#include <SFML/Graphics.hpp>



namespace turbohikerSFML {

    class RacingHiker : public turbohiker::RacingHiker {
    public:
        RacingHiker() = default;
        RacingHiker(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile);
        void init();

        void display () override;
        void update(float dTime) override;

        void move(const std::pair<double, double> &offset) override;
        void setPosition(const std::pair<double, double> &_position) override;
        void setVelocity(const std::pair<double, double> &_velocity) override;
        void setSize(const std::pair<double, double> &_size) override;
        void setOrigin(const std::pair<double, double> &_origin) override;

    private:
        std::weak_ptr<sf::RenderWindow> window;
        std::unique_ptr<Animation> anim;
        std::shared_ptr<sf::Texture> racerTexture;
        std::unique_ptr<sf::RectangleShape> racerRect;
        bool textureFlipped = false;

        int runAnimation;
    };

}