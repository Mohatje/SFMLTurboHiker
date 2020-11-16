#ifndef SFMLTURBOHIKER_ANIMATION_H
#include <SFML/Graphics.hpp>
#include <memory>
#define SFMLTURBOHIKER_ANIMATION_H

namespace turbohikerSFML {
    class Animation {
    public:
        Animation(std::unique_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float timeToSwitch);
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


#endif //SFMLTURBOHIKER_ANIMATION_H
