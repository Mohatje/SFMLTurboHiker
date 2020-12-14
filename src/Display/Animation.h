#pragma once
#include <SFML/Graphics.hpp>
#include <memory>


namespace turbohikerSFML {
    class Animation {
    public:
        Animation(std::shared_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float timeToSwitch);
        virtual ~Animation();

        void update(int row, float time, bool flip = false);

    public:
        sf::IntRect textureRect;
    private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float elapsedTime;
        float timeToSwitch;
    };

}
