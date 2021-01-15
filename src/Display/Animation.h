#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace turbohikerSFML {
class Animation
{
public:
        /**
         * Constructor for the Animation Class
         * @param texture texture which contains the animations
         * @param imageCount tuple of integers that describes how many images there are within the texture
         * @param timeToSwitch frametime (time to switch to the next animation frame)
         */
        Animation(std::shared_ptr<sf::Texture>& texture, sf::Vector2u imageCount, float timeToSwitch);
        virtual ~Animation();

        /**
         * Getter for the frametime of the animation
         * @return frametime
         */
        float getFrameTime() const;

        /**
         * Setter for the frametime of the animation
         * @param frameTime animation frametime
         */
        void setFrameTime(float frameTime);

        /**
         * Update method which updates the animation
         * @param row the animation row within the texture with animations
         * @param time time since last animation update
         * @param flip whether or not to flip the texture (facing left vs facing right)
         */
        void update(int row, float time, bool flip = false);

public:
        sf::IntRect textureRect;

private:
        sf::Vector2u imageCount;
        sf::Vector2u currentImage;

        float elapsedTime;
        float frameTime;
};

} // namespace turbohikerSFML
