#include "PassingHiker1.h"
#include "../Logic/Random.h"
#include "Transformation.h"


namespace turbohikerSFML {
    std::unique_ptr<sf::Texture> PassingHiker1::obstacleTexture ( new sf::Texture() );

    PassingHiker1::PassingHiker1(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile) : _window(window) {
        auto tilePath = configFile["StaticObstacle"]["Texture"].as_string_or_default("./media/Tiles/tileSet.png");
        auto activePair = configFile["StaticObstacle"]["ActiveTile"].as_int_tuple_or_default( {14, 0} );
        auto inactivePair = configFile["StaticObstacle"]["InactiveTile"].as_int_tuple_or_default( {13, 0} );


        obstacleRect = std::unique_ptr<sf::RectangleShape> (new sf::RectangleShape ( ));

        if (!(obstacleTexture->getSize().x > 0 && obstacleTexture->getSize().y > 0)) {
            if (!obstacleTexture->loadFromFile( tilePath )) {
                std::cerr << "Cannot load texture " << tilePath << ". Please check the configuration file." << std::endl;
            }
        }

        activeRect.width = 32;
        activeRect.height = 32;
        activeRect.left = activePair[0] * activeRect.width;
        activeRect.top = activePair[1] * activeRect.height;
        obstacleRect->setTexture(obstacleTexture.get());

        inactiveRect.width = 32;
        inactiveRect.height = 32;
        inactiveRect.left = inactivePair[0] * inactiveRect.width;
        inactiveRect.top = inactivePair[1] * inactiveRect.height;
        obstacleRect->setTextureRect(activeRect);

        init();

    }

    void PassingHiker1::init() {
        setSize( {0.50, 0.50} );
        setOrigin( {getSize().first / 2.0, getSize().second / 2.0} );
    }

    void PassingHiker1::spawn(double playerY) {
        int a = turbohiker::Random::randInt(-4, 4);
        int minY = static_cast<int>(playerY + 0.5) + 8;
        int b = turbohiker::Random::randInt(minY, minY + 5);
        double x, y;
        a < 4 ? x = a + 0.5 : x = a - 0.5;
        y = b + 0.5;
        setPosition( { x, y } );
    }

    bool PassingHiker1::doTypeSpecificAction() {
        if (!isActive()) {
            obstacleRect->setTextureRect(inactiveRect);
            return true;
        }
        return false;
    }

    void PassingHiker1::display() {
        _window.lock()->draw( *obstacleRect );
    }

    void PassingHiker1::update(float dTime) {
    }

    void PassingHiker1::setPosition(const std::pair<double, double> &_position) {
        Entity::setPosition(_position);

        obstacleRect->setPosition(Transformation::convertPosToPixels(*_window.lock(), _position));
    }

    void PassingHiker1::setSize(const std::pair<double, double> &_size) {
        Entity::setSize(_size);
        auto convertedSize = Transformation::convertSizeToPixels(*_window.lock(), _size);

        obstacleRect->setSize(convertedSize);
    }

    void PassingHiker1::setOrigin(const std::pair<double, double> &_origin) {
        Entity::setOrigin(_origin);
        auto convertedOrigin = Transformation::convertSizeToPixels(*_window.lock(), { _origin.first, getSize().second - _origin.second });
        obstacleRect->setOrigin( convertedOrigin );
    }

    void PassingHiker1::move(const std::pair<double, double> &offset) {
    }
}

