#include "Player.h"
#include "KeyConfigHelper.h"
#include "Transformation.h"

namespace turbohikerSFML {

Player::Player(const std::weak_ptr<sf::RenderWindow>& window, const ini::Configuration& configFile) : _window(window)
{

        // Loading hikers parameters and loading textures & sounds then initializing

        std::string texturePath = configFile["Player"]["Texture"].as_string_or_die();
        std::string yellPath = configFile["Player"]["YellSound"].as_string_or_die();
        playerTexture = std::make_shared<sf::Texture>();
        yellSound = std::make_shared<sf::SoundBuffer>();
        playerSound = std::make_shared<sf::Sound>();

        if (!playerTexture->loadFromFile(texturePath)) {
                std::cerr << "Cannot load texture " << texturePath << ". Please check the configuration file."
                          << std::endl;
        }

        if (!yellSound->loadFromFile(yellPath)) {
                std::cerr << "Cannot load audio file " << yellPath << ". Please check the configuration file."
                          << std::endl;
        }
        playerSound->setBuffer(*yellSound);
        playerSound->setVolume(35.f);

        unsigned int rows = configFile["Player"]["RowCount"].as_int_or_default(1);
        unsigned int cols = configFile["Player"]["ColumnCount"].as_int_or_default(1);
        float frameTime = configFile["Player"]["FrameTime"].as_double_or_default(1.0 / cols);

        runAnimation = configFile["Player"]["RunAnimation"].as_int_or_default(1);

        // Player controls
        Left = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Left"].as_string_or_default("A"));
        Right = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Right"].as_string_or_default("D"));
        Up = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Up"].as_string_or_default("W"));
        Down = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Down"].as_string_or_default("S"));
        Yell = KeyConfigHelper::keyboardFromString(configFile["Controls"]["Yell"].as_string_or_default("Y"));

        init();

        anim = std::unique_ptr<Animation>(new Animation(playerTexture, {cols, rows}, frameTime));
}

void Player::init()
{
        playerRect = std::unique_ptr<sf::RectangleShape>(new sf::RectangleShape());
        setSize({0.5, 0.5});
        setPosition({-3.5, -2.0});
        setOrigin({getSize().first / 2.0, getSize().second / 2.0});
        playerRect->setTexture(playerTexture.get());
}

void Player::display() { _window.lock()->draw(*playerRect); }

void Player::update(float dTime)
{
        if (getCurState() == turbohiker::EntityAIState::Finished)
                return;

        auto curVelocity = getVelocity();

        // Velocity decay
        curVelocity.first -= (curVelocity.first * 8.0 * dTime); // Skidding for about 125ms after no input
        curVelocity.second -= (curVelocity.second * 8.0 * dTime);

        // input handling
        if (sf::Keyboard::isKeyPressed(Left)) {
                curVelocity.first -= 40.0 * dTime;
        }

        if (sf::Keyboard::isKeyPressed(Right)) {
                curVelocity.first += 40.0 * dTime;
        }

        if (sf::Keyboard::isKeyPressed(Down)) {
                curVelocity.second -= 30.0 * dTime;
        }

        if (sf::Keyboard::isKeyPressed(Up)) {
                curVelocity.second += 30.0 * dTime;
        }

        if (sf::Keyboard::isKeyPressed(Yell)) {
                playerSound->play();
                action = true;
        }

        if (getCurState() == turbohiker::EntityAIState::UnYell) {
                action = false;
                setCurState(turbohiker::EntityAIState::Idle);
        }

        textureFlipped = curVelocity.first < 0.0;

        float animModifier = std::abs(curVelocity.second) > 1.f ? std::abs(curVelocity.second) : 1.f;
        animModifier = animModifier > std::abs(curVelocity.first) ? animModifier : std::abs(curVelocity.first);

        anim->update(runAnimation, dTime * animModifier, textureFlipped);
        setVelocity(curVelocity);
        move({curVelocity.first * dTime, curVelocity.second * dTime});

        playerRect->setTextureRect(anim->textureRect);
}

bool Player::doTypeSpecificAction() { return action; }

void Player::move(const std::pair<double, double>& offset)
{
        Entity::move(offset);
        auto newPos = Transformation::convertPosToPixels(*_window.lock(), getPosition());

        playerRect->setPosition(newPos);
}

void Player::setPosition(const std::pair<double, double>& _position)
{
        Entity::setPosition(_position);

        playerRect->setPosition(Transformation::convertPosToPixels(*_window.lock(), _position));
}

void Player::setVelocity(const std::pair<double, double>& _velocity) { Entity::setVelocity(_velocity); }

void Player::setSize(const std::pair<double, double>& _size)
{
        Entity::setSize(_size);
        auto convertedSize = Transformation::convertSizeToPixels(*_window.lock(), _size);

        playerRect->setSize(convertedSize);
}

void Player::setOrigin(const std::pair<double, double>& _origin)
{
        Entity::setOrigin(_origin);
        auto convertedOrigin =
            Transformation::convertSizeToPixels(*_window.lock(), {_origin.first, getSize().second - _origin.second});
        playerRect->setOrigin(convertedOrigin);
}

} // namespace turbohikerSFML