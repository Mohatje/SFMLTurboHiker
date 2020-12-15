#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "../Logic/Entity.h"

namespace turbohikerSFML {

    class TileEntity : public turbohiker::Entity {
    public:
        TileEntity() = default;
        TileEntity(const std::weak_ptr<sf::RenderWindow> &window,
                   std::pair<double, double> position,
                   std::pair<double, double> size,
                   std::shared_ptr<sf::Texture> texture,
                   sf::Vector2u texPosition);


        void display() override;

        void update(float dT) override {}
        void doTypeSpecificAction() override {}
        void move(const std::pair<double, double>& offset) override;

        turbohiker::EntityType getType() const { return turbohiker::EntityType::Tile; }

        void setPosition(const std::pair<double, double> &_position) override;
        void setSize(const std::pair<double, double> &_size) override;
        void setOrigin(const std::pair<double, double> &_origin) override;

    private:
        std::weak_ptr<sf::RenderWindow> _window;
        std::shared_ptr<sf::Texture> tileSet;
        std::unique_ptr<sf::RectangleShape> tileRect;

        void init(std::pair<double, double> position, std::pair<double, double> size);
    };

}