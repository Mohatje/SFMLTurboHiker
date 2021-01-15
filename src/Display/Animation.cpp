#include "Animation.h"

namespace turbohikerSFML {
Animation::Animation(std::shared_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float _frameTime)
    : imageCount(imageCount), frameTime(_frameTime)
{
        elapsedTime = 0.f;
        currentImage.x = 0;

        textureRect.width = texture->getSize().x / static_cast<float>(imageCount.x);
        textureRect.height = texture->getSize().y / static_cast<float>(imageCount.y);
}

Animation::~Animation() {}

void Animation::update(int row, float time, bool flip)
{
        // keep track on which row of the texture we're on
        currentImage.y = row;

        // add the game frametime to the elapsed time
        elapsedTime += time;

        // if the elapsed time is higher than the animation's frametime, then we update the textureRect
        if (elapsedTime >= frameTime) {
                elapsedTime -= frameTime;
                // next frame
                currentImage.x++;
                // go back to 0th frame
                if (currentImage.x >= imageCount.x)
                        currentImage.x = 0;
        }

        if (flip) {
                // calculate rect's with
                textureRect.width = -std::abs(textureRect.width);
                // based on which frame we can offset the rect to that
                textureRect.left = (currentImage.x + 1) * abs(textureRect.width);
        } else {
                textureRect.width = std::abs(textureRect.width);
                textureRect.left = currentImage.x * textureRect.width;
        }
        // Rect's height & top solely based on image dimensions and current row
        textureRect.top = currentImage.y * textureRect.height;
}

float Animation::getFrameTime() const { return frameTime; }

void Animation::setFrameTime(float frameTime) { Animation::frameTime = frameTime; }
} // namespace turbohikerSFML