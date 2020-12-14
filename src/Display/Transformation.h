#pragma once
#include <SFML/Graphics.hpp>


namespace turbohikerSFML {
    class Transformation {
    public:

        /**
         * Static method to get the Transformation class object, this is a unique object
         * @return Transformation class object
         */
        static Transformation& getInstance();


        /**
         * Transforms pixel values to game world coordinate system [-4,4] x [-3,3]
         * @param window Const reference to the game window, used to get window size
         * @param window_position Unsigned tuple of pixel coordinates
         * @return Tuple of floats within the game world coordinate system
         */
        static std::pair<double, double> convertPosFromPixels(const sf::Window& window, const sf::Vector2f& window_position);

        /**
         * Transforms game world coordinates to pixels
         * @param window Const reference to the game window, used to get window size
         * @param world_position Position within the game coordinate sytem.
         * @return Unsinged int tuple to the pixel values of the given coordinate
         */
        static sf::Vector2f convertPosToPixels(const sf::Window& window, const std::pair<double, double>& world_position);


        static sf::Vector2f convertSizeToPixels(const sf::Window &window, const std::pair<double, double> &world_size);

        static std::pair<double, double> convertSizeFromPixels(const sf::Window &window, const sf::Vector2f &window_position);

    private:
        Transformation() = default; // Use of a private constructor to prevent the construction of more than 1 instance
        Transformation(const Transformation& cpy);
        Transformation& operator=(const Transformation& rhs);
        ~Transformation() = default;
    };
}