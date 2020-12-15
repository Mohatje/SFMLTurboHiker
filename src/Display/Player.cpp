#include "Player.h"
#include "KeyConfigHelper.h"
#include "Transformation.h"


namespace turbohikerSFML {


    Player::Player(const std::weak_ptr<sf::RenderWindow> &window,
                            const ini::Configuration &configFile) : _window(window) {

        std::string texturePath = configFile["Player"]["Texture"].as_string_or_die();
        playerTexture = std::make_shared<sf::Texture>(  );

//        if (!playerTexture->loadFromFile( texturePath )) {
//            std::cerr << "Cannot load texture " << texturePath << ". Please check the configuration file." << std::endl;
//        }

        unsigned int rows = configFile["Player"]["RowCount"].as_int_or_default(1);
        unsigned int cols = configFile["Player"]["ColumnCount"].as_int_or_default(1);
        float frameTime = configFile["Player"]["FrameTime"].as_double_or_default(1.0 / cols);

        idleAnimation = configFile["Player"]["IdleAnimation"].as_int_or_default(0);
        runAnimation = configFile["Player"]["RunAnimation"].as_int_or_default(1);

        // Player controls
        Left = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Left"].as_string_or_default("A"));
        Right = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Right"].as_string_or_default("D"));
        Up = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Up"].as_string_or_default("W"));
        Down = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Down"].as_string_or_default("S"));
        Yell = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Yell"].as_string_or_default("Y"));

        init();

        anim = std::unique_ptr<Animation> (new Animation(playerTexture, {cols, rows}, frameTime));
    }

    void Player::init() {
        playerRect = std::unique_ptr<sf::RectangleShape> (new sf::RectangleShape());
        setSize({1.00, 1.00});
        setPosition({0, 0});
        setOrigin( {0.5, 0.5} );
        playerRect->setTexture(playerTexture.get());

    }

    void Player::display() {
        _window.lock()->draw(*playerRect);

    }

    void Player::update(float dTime) {
        auto curVelocity = getVelocity();

        // Velocity decay
        curVelocity.first -= ( curVelocity.first * 12.0 * dTime ); // Skidding for about 125ms after no input
        curVelocity.second -= ( curVelocity.second * 12.0 * dTime );


        if (sf::Keyboard::isKeyPressed(Left)) {
            textureFlipped = true;
            curVelocity.first -= 0.75;
        }

        if (sf::Keyboard::isKeyPressed(Right)) {
            textureFlipped = false;
            curVelocity.first += 0.75;
        }

        if (sf::Keyboard::isKeyPressed(Down)) {
            curVelocity.second -= 0.60;
        }

        if (sf::Keyboard::isKeyPressed(Up)) {
            curVelocity.second += 0.60;
        }

        if (sf::Keyboard::isKeyPressed(Yell)) {
        }


        if ((std::abs(curVelocity.first) > 1.0f) || (std::abs(curVelocity.second) > 1.0f) )
            anim->update(runAnimation, dTime, textureFlipped);
        else
            anim->update(idleAnimation, dTime, textureFlipped);

        curVelocity.first = std::max(std::min(curVelocity.first, 2.0), -2.0);
        curVelocity.second = std::max(std::min(curVelocity.second, 2.0), -2.0);
        setVelocity(curVelocity);
        move( {curVelocity.first * dTime, curVelocity.second * dTime} );



        playerRect->setTextureRect(anim->textureRect);
    }

    void Player::move(const std::pair<double, double> &offset) {
        auto curPosition = getPosition();
        auto newOffset = offset;
        if (curPosition.first + offset.first > 3.5 || curPosition.first + offset.first < -3.5)
            newOffset.first = 0;
        Entity::move(newOffset);
        auto newPos = Transformation::convertPosToPixels(*_window.lock(), getPosition());

        playerRect->setPosition(newPos);
    }

    void Player::setPosition(const std::pair<double, double> &_position) {
        Entity::setPosition(_position);

        playerRect->setPosition(Transformation::convertPosToPixels(*_window.lock(), _position));
    }

    void Player::setVelocity(const std::pair<double, double> &_velocity) {
        Entity::setVelocity(_velocity);
    }

    void Player::setSize(const std::pair<double, double> &_size) {
        Entity::setSize(_size);
        auto convertedSize = Transformation::convertSizeToPixels(*_window.lock(), _size);

        playerRect->setSize(convertedSize);
    }

    void Player::setOrigin(const std::pair<double, double> &_origin) {
        Entity::setOrigin(_origin);
        auto convertedOrigin = Transformation::convertSizeToPixels(*_window.lock(), { _origin.first, getSize().second - _origin.second });
        playerRect->setOrigin( convertedOrigin );
    }


}