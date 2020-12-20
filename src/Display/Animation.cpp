#include "Animation.h"


namespace turbohikerSFML {
    Animation::Animation(std::shared_ptr<sf::Texture> &texture, sf::Vector2u imageCount, float _frameTime) :
                                                             imageCount(imageCount), frameTime(_frameTime) {
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

        if (elapsedTime >= frameTime) {
            elapsedTime -= frameTime;
            currentImage.x++;
            if (currentImage.x >= imageCount.x)
                currentImage.x = 0;
        }

        if (flip) {
            textureRect.width = -std::abs(textureRect.width);
            textureRect.left = (currentImage.x + 1) * abs(textureRect.width);
        } else {
            textureRect.width = std::abs(textureRect.width);
            textureRect.left = currentImage.x * textureRect.width;
        }
        textureRect.top = currentImage.y * textureRect.height;

    }

    float Animation::getFrameTime() const {
        return frameTime;
    }

    void Animation::setFrameTime(float frameTime) {
        Animation::frameTime = frameTime;
    }
}