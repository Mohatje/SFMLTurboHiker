#pragma once
#include "FactoryCreator.h"
#include "../Parser/ini_configuration.h"
#include "World.h"
#include "../Logic/GameAI.h"
#include "../Logic/LeaderBoard.h"


namespace turbohikerSFML {

    class Game {
    public:
        Game();
        Game(const std::string &configPath );
        ~Game() = default;

    public:
        void run();
        void init();
        void cleanup();

    private:
        Game(const Game& copy);
        Game& operator=(const Game& rhs);

    private:
        using EntityRef = std::unique_ptr<turbohiker::Entity>;

        std::unique_ptr<turbohiker::AbstractFactory> entFactory;
        ini::Configuration config;
        std::shared_ptr<sf::RenderWindow> window;

        std::shared_ptr<World> world;
        std::shared_ptr<sf::Texture> tileSet;
        sf::View gameView;
        sf::Font gameFont;
        turbohiker::LeaderBoard leaderBoard;

        std::string playerName;
        sf::Text playerScore;

        bool finishDrawn = false;
        bool gameFinished = false;
        double lastDrawnY = 3.0;
        double finishLine = 0.0;
        double timeToFinish = 10.0;

    private:
        void generateMap();
        void correctOutOfBounds();
        void generateStrip(sf::Vector2u Left, sf::Vector2u Middle, sf::Vector2u Right, double y);

        void tryToDraw();
        void spawnObstacle();
        void addColliders();
        void addRacers();
        void spawnFinishLine();

        void calculateView(float dTime);
        void displayScore();
    };

}

