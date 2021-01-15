#pragma once
#include "../Logic/Entity.h"
#include <SFML/Graphics.hpp>
#include <memory>

namespace turbohikerSFML {

class TileEntity : public turbohiker::Entity
{
public:
        /**
         * Default constructor
         */
        TileEntity() = default;

        /**
         * Tile entity constructor
         * @param window        weak pointer to game window
         * @param position      tile entity position
         * @param size          tile entity size
         * @param texture       tile entity texture
         * @param texPosition   tile entity position within the texture (using tile map)
         * @param stationary    whether or not the entity should move with the game view
         */
        TileEntity(const std::weak_ptr<sf::RenderWindow>& window, std::pair<double, double> position,
                   std::pair<double, double> size, std::shared_ptr<sf::Texture> texture, sf::Vector2u texPosition,
                   bool stationary = false);

        void display() override;

        void update(float dT) override {}
        bool doTypeSpecificAction() override { return false; }
        void move(const std::pair<double, double>& offset) override;

        turbohiker::EntityType getType() const override { return turbohiker::EntityType::Tile; }

        void setPosition(const std::pair<double, double>& _position) override;
        void setSize(const std::pair<double, double>& _size) override;
        void setOrigin(const std::pair<double, double>& _origin) override;

        /**
         * Change whether or not the entity should move with the game view
         * @param _static   true if not moving, false if moving
         */
        void setStatic(bool _static);

private:
        std::weak_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::Texture> tileSet;
        std::unique_ptr<sf::RectangleShape> tileRect;

        void init(std::pair<double, double> position, std::pair<double, double> size);

        bool stationary;
};

} // namespace turbohikerSFML