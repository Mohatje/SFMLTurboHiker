#include "PassingHiker2.h"
#include "../Logic/Random.h"
#include "Transformation.h"


namespace turbohikerSFML {

    PassingHiker2::PassingHiker2(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile) : _window(window) {

        // Loading hikers parameters and loading textures then initializing

        std::string txPath = configFile["MovingObstacle"]["Texture"].as_string_or_default("./media/Pipoya/Enemy/Enemy 06-1.png");
        obstacleRect = std::unique_ptr<sf::RectangleShape> (new sf::RectangleShape( ) );
        obstacleTexture = std::make_shared<sf::Texture> ( );

        if (!obstacleTexture->loadFromFile(txPath))
            std::cerr   << "Cannot load moving enemy texture "
                        << txPath << ". Please check the configuration file." << std::endl;

        unsigned int rows = configFile["MovingObstacle"]["RowCount"].as_int_or_default(1);
        unsigned int cols = configFile["MovingObstacle"]["ColumnCount"].as_int_or_default(1);
        float frameTime = configFile["MovingObstacle"]["FrameTime"].as_double_or_default(1.0 / cols);

        runAnimation = configFile["MovingObstacle"]["RunAnimation"].as_int_or_default(1);

        init();

        anim = std::unique_ptr<Animation> (new Animation(obstacleTexture, {cols, rows}, frameTime) );
    }

    void PassingHiker2::init() {
        setSize( {0.5, 0.5} );
        setOrigin( { getSize().first / 2.0, getSize().second / 2.0 } );
        obstacleRect->setTexture(obstacleTexture.get());
        setVelocity( {0.0, -3.5} );
    }

    bool PassingHiker2::doTypeSpecificAction() {
        return isActive();
    }

    void PassingHiker2::update(float dTime) {
        turbohiker::PassingHiker2::update(dTime);
        anim->update(runAnimation, dTime);
        obstacleRect->setTextureRect(anim->textureRect);
    }

    void PassingHiker2::display() {
        _window.lock()->draw(*obstacleRect);
    }

    void PassingHiker2::move(const std::pair<double, double> &offset) {
        Entity::move(offset);
        auto newPos = Transformation::convertPosToPixels(*_window.lock(), getPosition());

        obstacleRect->setPosition(newPos);
    }

    void PassingHiker2::setPosition(const std::pair<double, double> &_position) {
        Entity::setPosition(_position);
        auto newPos = Transformation::convertPosToPixels(*_window.lock(), _position);

        obstacleRect->setPosition(newPos);
    }

    void PassingHiker2::setSize(const std::pair<double, double> &_size) {
        Entity::setSize(_size);
        auto convertedSize = Transformation::convertSizeToPixels(*_window.lock(), _size);

        obstacleRect->setSize(convertedSize);
    }

    void PassingHiker2::setOrigin(const std::pair<double, double> &_origin) {
        Entity::setOrigin(_origin);
        auto convertedOrigin = Transformation::convertSizeToPixels(*_window.lock(), { _origin.first, getSize().second - _origin.second });
        obstacleRect->setOrigin( convertedOrigin );
    }

}