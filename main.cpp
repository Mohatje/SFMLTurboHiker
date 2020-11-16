#include <iostream>
#include <SFML/Graphics.hpp>
#include "DEFINES.h"
#include "src/Animation.h"


int main() {

    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!",
                            sf::Style::Close | sf::Style::Titlebar);

    std::unique_ptr<sf::Texture> hikerTexture{new sf::Texture};
    hikerTexture->loadFromFile(MEDIA "/HikerSprites/sprite-sheet-v2.png");

    sf::RectangleShape player({200.f, 148.f});
    player.setOrigin({50.f, 75.f});
    player.setPosition(640, 360);
    player.setTexture(hikerTexture.get());

    turbohikerSFML::Animation animation(hikerTexture, sf::Vector2u(4, 3), 0.25f);

    float dTime = 0.f;
    sf::Clock clock;
    while (window.isOpen())
    {
        dTime = clock.restart().asSeconds();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) {
            auto mousePos = sf::Mouse::getPosition(window);
            player.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }

        animation.update(0, dTime);
        player.setTextureRect(animation.textureRect);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            animation.update(1, dTime);
            player.setTextureRect(animation.textureRect);
            player.move({0.0f, 0.0f});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            animation.update(2, dTime);
            player.setTextureRect(animation.textureRect);
            player.move({0.0f, 0.0f});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            animation.update(2, dTime, true);
            player.setTextureRect(animation.textureRect);
            player.move({0.0f, 0.0f});
        }

        window.clear(sf::Color(150, 150, 150));
        window.draw(player);
        window.display();
    }

    return 0;
}
