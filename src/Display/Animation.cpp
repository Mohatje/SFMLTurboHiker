#include "Animation.h"


namespace turbohikerSFML {
    Animation::Animation(std::shared_ptr<sf::Texture> &texture, sf::Vector2u imageCount,
                                         float timeToSwitch) {
        this->imageCount = imageCount;
        this->timeToSwitch = timeToSwitch;

        elapsedTime = 0.f;
        currentImage.x = 0;

        textureRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
        textureRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
    }

    Animation::~Animation() {
    }

    void Animation::update(int row, float time, bool flip) {
        currentImage.y = row;
        elapsedTime += time;

        if (elapsedTime >= timeToSwitch) {
            elapsedTime -= timeToSwitch;
            currentImage.x++;
            if (currentImage.x >= imageCount.x)
                currentImage.x = 0;
        }

        textureRect.top = currentImage.y * textureRect.height;
        if (flip) {
            textureRect.left = (currentImage.x + 1) * abs(textureRect.width);
            textureRect.width = -abs(textureRect.width);
        } else {
            textureRect.left = currentImage.x * textureRect.width;
            textureRect.width = abs(textureRect.width);
        }

    }
}