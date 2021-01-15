#include "Transformation.h"

namespace turbohikerSFML {

Transformation& Transformation::getInstance()
{
        static Transformation instance;
        return instance;
}

std::pair<double, double> Transformation::convertPosFromPixels(const sf::Window& window,
                                                               const sf::Vector2f& window_position)
{
        sf::Vector2u wSize = window.getSize();
        std::pair<double, double> ret{((window_position.x / wSize.x) * 8) - 4,
                                      (3.0f - (window_position.y / wSize.y) * 6)};
        return ret;
}

std::pair<double, double> Transformation::convertSizeFromPixels(const sf::Window& window,
                                                                const sf::Vector2f& window_position)
{
        sf::Vector2u wSize = window.getSize();
        std::pair<double, double> ret{(window_position.x / wSize.x) * 8, (window_position.y / wSize.y) * 6};
        return ret;
}

sf::Vector2f Transformation::convertPosToPixels(const sf::Window& window,
                                                const std::pair<double, double>& world_position)
{
        sf::Vector2u wSize = window.getSize();
        double x = ((world_position.first + 4.0f) / 8.0f) * wSize.x;
        double y = ((3.0f - world_position.second) / 6.0f) * wSize.y;

        return {float(x), float(y)};
}

sf::Vector2f Transformation::convertSizeToPixels(const sf::Window& window, const std::pair<double, double>& world_size)
{
        auto wSize = window.getSize();

        return {float((world_size.first / 8.0f) * wSize.x), float((world_size.second / 6.0f) * wSize.y)};
}

} // namespace turbohikerSFML