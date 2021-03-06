#pragma once
#include "../Logic/GameAI.h"
#include "../Parser/ini_configuration.h"
#include "Animation.h"
#include "FactoryCreator.h"
#include "LeaderBoard.h"
#include "World.h"

namespace turbohikerSFML {

class Game
{
public:
        /**
         * Default game constructor, uses "./Config/config.ini" as config file path by default
         */
        Game();

        /**
         * Game constructor
         * @param configPath config file path
         */
        Game(const std::string& configPath);
        ~Game() = default;

public:
        /**
         * Method to run the game
         */
        void run();

        /**
         * Method used for initializing the game
         */
        void init();

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

        std::shared_ptr<sf::Texture> finishTexture;
        std::unique_ptr<Animation> finishAnimation;
        std::vector<sf::RectangleShape> finishPortals;

        sf::View gameView;
        sf::Font gameFont;
        LeaderBoard leaderBoard;

        std::string playerName;
        sf::Text playerScore;

        bool finishDrawn = false;
        bool gameFinished = false;
        double lastDrawnY = 3.0;
        double finishLine = 0.0;
        double timeToFinish = 30.0;

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

        void generateFinishPortals(double _lastDrawnY);
};

} // namespace turbohikerSFML
