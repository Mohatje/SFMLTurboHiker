#pragma once
#include <SFML/Graphics.hpp>
#include "../Logic/LeaderBoard.h"


namespace turbohikerSFML {

    class LeaderBoard : public turbohiker::LeaderBoard {
    public:

        /**
         * Default Constructor
         */
        LeaderBoard() = default;

        /**
         * Method to initialize the LeaderBoard
         * @param window game window
         * @param userFont the to be used font
         * @param texturePath background texture for the leaderboard
         */
        void init(std::shared_ptr<sf::RenderWindow> &window, const sf::Font &userFont, std::string texturePath);

        /**
         * Display method to display the leaderboard
         * @param playerName name of the player, to be used to load the highscore
         */
        void display(std::string &playerName);

    private:
        float windowScalar;
        sf::Texture lbTexture;
        sf::RectangleShape lbShape;
        std::shared_ptr<sf::RenderWindow> _window;
        sf::Text title;
        sf::Text scores;
        sf::Text personalBest;
    };

}

