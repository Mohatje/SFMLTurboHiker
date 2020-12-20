#include "RacingHiker.h"
#include "Transformation.h"

namespace turbohikerSFML {

    RacingHiker::RacingHiker(const std::weak_ptr<sf::RenderWindow> &window, const ini::Configuration &configFile) : window(window) {
        std::string texturePath = configFile["RacingHiker"]["Texture"].as_string_or_die();
        racerTexture = std::make_shared<sf::Texture> ( );

        if (!racerTexture->loadFromFile(texturePath))
            std::cerr << "Cannot load texture " << texturePath << ". Please check the configuration file." << std::endl;

        unsigned int rows = configFile["RacingHiker"]["RowCount"].as_int_or_default(1);
        unsigned int cols = configFile["RacingHiker"]["ColumnCount"].as_int_or_default(1);
        float frameTime = configFile["RacingHiker"]["FrameTime"].as_double_or_default(1.0 / cols);

        runAnimation = configFile["Player"]["RunAnimation"].as_int_or_default(3);

        init();

        anim = std::unique_ptr<Animation> (new Animation(racerTexture, {cols, rows}, frameTime));
    }

    void RacingHiker::init() {
        racerRect = std::unique_ptr<sf::RectangleShape> (new sf::RectangleShape);
        setSize({0.5, 0.5});
        setPosition( {0, 0} );
        setOrigin( {getSize().first / 2.0, getSize().second / 2.0 } );
        racerRect->setTexture(racerTexture.get());
    }

    void RacingHiker::display() {
        window.lock()->draw(*racerRect);
    }

    void RacingHiker::update(float dTime) {
        turbohiker::RacingHiker::update(dTime);
        auto curVelocity = getVelocity();
        textureFlipped = curVelocity.first < 0.0;
        double animModifier = std::abs(curVelocity.second) > 1.f ? std::abs(curVelocity.second) : 1.f;
        animModifier = animModifier > std::abs(curVelocity.first) ? animModifier : std::abs(curVelocity.first);

        anim->update(runAnimation, dTime * float(animModifier), textureFlipped);
        racerRect->setTextureRect(anim->textureRect);
    }

    void RacingHiker::move(const std::pair<double, double> &offset) {
        Entity::move(offset);
        auto newPos = Transformation::convertPosToPixels(*window.lock(), getPosition());

        racerRect->setPosition(newPos);
    }

    void RacingHiker::setPosition(const std::pair<double, double> &_position) {
        Entity::setPosition(_position);

        racerRect->setPosition(Transformation::convertPosToPixels(*window.lock(), _position));
    }

    void RacingHiker::setVelocity(const std::pair<double, double> &_velocity) {
        Entity::setVelocity(_velocity);
    }

    void RacingHiker::setSize(const std::pair<double, double> &_size) {
        Entity::setSize(_size);
        auto convertedSize = Transformation::convertSizeToPixels(*window.lock(), _size);

        racerRect->setSize(convertedSize);
    }

    void RacingHiker::setOrigin(const std::pair<double, double> &_origin) {
        Entity::setOrigin(_origin);
        auto convertedOrigin = Transformation::convertSizeToPixels(*window.lock(), { _origin.first, getSize().second - _origin.second });
        racerRect->setOrigin( convertedOrigin );
    }



}