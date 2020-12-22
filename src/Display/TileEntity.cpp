#include "TileEntity.h"
#include "Transformation.h"
#include <iostream>


namespace turbohikerSFML {
    TileEntity::TileEntity(const std::weak_ptr<sf::RenderWindow> &window,
                           std::pair<double, double> position,
                           std::pair<double, double> size,
                           std::shared_ptr<sf::Texture> texture,
                           sf::Vector2u texPosition,
                           bool stationary) : _window(window), tileSet(texture), stationary(stationary) {

        tileRect = std::unique_ptr<sf::RectangleShape> (new sf::RectangleShape(  ));
        if (texture == nullptr) {
            tileRect->setFillColor(sf::Color::Transparent);
        } else {
            tileRect->setTexture(tileSet.get());
            sf::IntRect tileTextRect;
            tileTextRect.width = 32;
            tileTextRect.height = 32;
            tileTextRect.left = texPosition.x * tileTextRect.width;
            tileTextRect.top = texPosition.y * tileTextRect.height;
            tileRect->setTextureRect(tileTextRect);
        }

        init(position, size);

    }

    void TileEntity::init(std::pair<double, double> position, std::pair<double, double> size) {
        setSize(size);
        setPosition(position);
        setOrigin( { size.first / 2.0,  size.second / 2 } );
    }

    void TileEntity::display() {
        _window.lock()->draw(*tileRect);
    }

    void TileEntity::setPosition(const std::pair<double, double> &_position) {
        Entity::setPosition(_position);

        tileRect->setPosition(Transformation::convertPosToPixels(*_window.lock(), _position));
    }

    void TileEntity::setSize(const std::pair<double, double> &_size) {
        Entity::setSize(_size);

        tileRect->setSize(Transformation::convertSizeToPixels(*_window.lock(), _size));

    }

    void TileEntity::setOrigin(const std::pair<double, double> &_origin) {
        Entity::setOrigin(_origin);
        auto convertedOrigin = Transformation::convertSizeToPixels(*_window.lock(), { _origin.first, getSize().second - _origin.second });
        tileRect->setOrigin( convertedOrigin );
    }

    void TileEntity::move(const std::pair<double, double>& offset) {
        if (stationary) return;
        Entity::move(offset);
        auto newPos = Transformation::convertPosToPixels(*_window.lock(), getPosition());

        tileRect->setPosition(newPos);
    }

    void TileEntity::setStatic(bool _static) {
        stationary = _static;
    }
}