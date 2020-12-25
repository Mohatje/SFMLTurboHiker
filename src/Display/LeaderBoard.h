#pragma once
#include <SFML/Graphics.hpp>
#include "../Logic/LeaderBoard.h"


namespace turbohikerSFML {

    class LeaderBoard : public turbohiker::LeaderBoard {
    public:
        LeaderBoard() = default;

        void init(std::shared_ptr<sf::RenderWindow> &window, const sf::Font &userFont, std::string texturePath);
        void display(std::string &playerName);
    private:
        sf::Texture lbTexture;
        sf::RectangleShape lbShape;
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Text title;
        sf::Text scores;
        sf::Text personalBest;
    };

}

