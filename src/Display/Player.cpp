#include "Player.h"
#include "KeyConfigHelper.h"
#include "Transformation.h"


namespace turbohikerSFML {


    Player::Player(const std::weak_ptr<sf::RenderWindow> &window,
                            const ini::Configuration &configFile) : _window(window) {

        std::string texturePath = configFile["Player"]["Texture"].as_string_or_die();
        playerTexture = std::make_shared<sf::Texture>( );

        if (!playerTexture->loadFromFile( texturePath )) {
            std::cerr << "Cannot load texture " << texturePath << ". Please check the configuration file." << std::endl;
        }

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

        // this->setSize({0.20, 0.60});
        playerRect = std::unique_ptr<sf::RectangleShape> (new sf::RectangleShape({200.f, 148.f}));
        playerRect->setOrigin({100.f, 148.f});
        playerRect->setPosition(640, 360);
        playerRect->setTexture(playerTexture.get());

        anim = std::unique_ptr<Animation> (new Animation(playerTexture, {cols, rows}, frameTime));
    }

    void Player::display() {
        _window.lock()->draw(*playerRect);

    }

    void Player::update(float dTime) {
//        bool run = false;

        anim->update(idleAnimation, dTime);

        auto curVelocity = getVelocity();

//        std::pair<double, double> curVelocity {0, 0};

        // Velocity decay
        std::cout << curVelocity.first << std::endl;
        curVelocity.first -= (curVelocity.first * 4.0 * dTime ); // Skidding for 250ms after no input
        curVelocity.second -= (curVelocity.second * 4.0 * dTime );
        std::cout << curVelocity.first << "\t" << dTime << std::endl;

        if (sf::Keyboard::isKeyPressed(Left)) {
//            run = true;
            textureFlipped = true;
            curVelocity.first -= (0.25 * dTime);
        }

        if (sf::Keyboard::isKeyPressed(Right)) {
//            run = true;
            textureFlipped = false;
            curVelocity.first += (0.25 * dTime);
        }

        if (sf::Keyboard::isKeyPressed(Down)) {
//            run = true;
            curVelocity.second -= (0.10 * dTime);
        }

        if (sf::Keyboard::isKeyPressed(Up)) {
//            run = true;
            curVelocity.second += (0.10 * dTime);
        }

        if (sf::Keyboard::isKeyPressed(Yell)) {
        }

//        run ? anim->update(runAnimation, dTime, textureFlipped) : anim->update(idleAnimation, dTime, false);

        if ((std::abs(curVelocity.first) > 5e-3) || (std::abs(curVelocity.second) > 5e-3) )
            anim->update(runAnimation, dTime, textureFlipped);
        else
            anim->update(idleAnimation, dTime, textureFlipped);

        curVelocity.first = std::max(std::min(curVelocity.first, 0.1), -0.1);
        curVelocity.second = std::max(std::min(curVelocity.second, 0.1), -0.1);
        setVelocity(curVelocity);
        move(curVelocity);



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

        playerRect->setSize(Transformation::convertSizeToPixels(*_window.lock(), _size));
    }


}