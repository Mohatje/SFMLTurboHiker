#include <iostream>


#include "./src/Display/Game.h"


int main() {


/*    sf::RenderWindow window(sf::VideoMode(config["Window"]["Width"].as_int_or_die(),
                                          config["Window"]["Height"].as_int_or_die()), "SFML works!",
                            sf::Style::Close | sf::Style::Titlebar);

    std::shared_ptr<sf::Texture> hikerTexture = std::make_shared<sf::Texture>();
    hikerTexture->loadFromFile(config["Player"]["Texture"]);

    std::unique_ptr<sf::RectangleShape> player(new sf::RectangleShape({200.f, 148.f}));
    player->setOrigin({100.f, 74.f});
    player->setPosition(640, 360);
    player->setTexture(hikerTexture.get());


    turbohikerSFML::Animation animation(hikerTexture, sf::Vector2u(4, 3), 0.25f);



    using CLOCK = std::chrono::high_resolution_clock;
    double dTime = 1.0;
    auto last = CLOCK::now();
    sf::Clock clock;
    window.setVerticalSyncEnabled(true);
    while (window.isOpen())
    {
        auto now = CLOCK::now();
        auto time_span = std::chrono::duration_cast <
                std::chrono::duration<double>> (
                        now - last);
        last = now;
        dTime = time_span.count();

        sf::Event event{};
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
            player->setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
        }

        animation.update(0, dTime);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            animation.update(1, dTime);
            player->move({0.0f, 0.0f});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            animation.update(2, dTime);
            player->move({250.f * float(dTime), 0.0f});
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            animation.update(2, dTime, true);
            player->move({-250.f * float(dTime), 0.0f});
        }
        player->setTextureRect(animation.textureRect);


        window.clear(sf::Color(150, 150, 150));
        window.draw(*player);
        window.display();
    }*/


    turbohikerSFML::Game game("./Config/config.ini");
    game.run();


    return EXIT_SUCCESS;
}
