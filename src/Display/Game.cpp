#include "../assertion.h"
#include "Game.h"
#include "PassingHiker1.h"
#include "PassingHiker2.h"
#include "../Logic/Random.h"
#include "TileEntity.h"
#include "Transformation.h"
#include "../Logic/ScoreObserver.h"
#include <chrono>

namespace turbohikerSFML {
    Game::Game() : Game("./Config/config.ini") {}

    Game::Game(const std::string &configPath) {

        try {
            std::ifstream config_in(configPath);
            config_in >> config;
        } catch(ini::ParseException &ex) {
            std::cerr   << "Error parsing file: "
                        << configPath << ": "
                        << ex.what() << std::endl;
        }

        int width = config["Window"]["Width"].as_int_or_default(1280);
        int height = config["Window"]["Height"].as_int_or_default(720);
        bool vsync = config["Window"]["VSync"].as_bool_or_default(false);
        bool fullscreen = config["Window"]["Fullscreen"].as_bool_or_default(false);

        std::string fontPath = config["Settings"]["FontPath"].as_string_or_die();
        if ( !gameFont.loadFromFile(fontPath) )
            std::cerr << "Could not load font " + fontPath + " . Please check the configuration file" << std::endl;



        if (fullscreen) {
            window = std::make_shared<sf::RenderWindow> (sf::VideoMode(width, height), "TurboHiker",
                                                         sf::Style::Fullscreen);
        }
        else {
            window = std::make_shared<sf::RenderWindow> (sf::VideoMode(width, height), "TurboHiker",
                          sf::Style::Close | sf::Style::Titlebar);

        }
        window->setVerticalSyncEnabled(vsync);

        leaderBoard.init(window, gameFont);

        this->init();
    }

    void Game::init() {

        playerName = config["Settings"]["PlayerName"].as_string_or_default("Player");


        playerScore.setFont(gameFont);
        playerScore.setCharacterSize(45);
        playerScore.setFillColor(sf::Color::White);
        playerScore.setOutlineColor(sf::Color::Black);
        playerScore.setOutlineThickness(2.5f);


        entFactory = FactoryCreator::getFactory("entity", window, config);
        EntityRef worldEnt = entFactory->createEntity(turbohiker::EntityType::World);
        if (worldEnt->getType() != turbohiker::EntityType::World)
            std::cerr << "Factory did not return a World entity." << std::endl;

        auto temp = dynamic_cast<World*> (worldEnt.release());
        ASSERT(temp != nullptr, "World pointer is not a valid World object.")
        world.reset(temp);

        world->addEntity(entFactory->createEntity(turbohiker::EntityType::Player));
        std::shared_ptr<turbohiker::Observer> playerObserver = std::make_shared<turbohiker::ScoreObserver> ( );
        leaderBoard.addObserver(playerName, playerObserver);
        world->getPlayerPtr()->addObserver(std::move(playerObserver));

        gameView.setSize(static_cast<sf::Vector2f> (window->getSize()));
        gameView.setCenter(static_cast<sf::Vector2f> (window->getSize()) / 2.0f);

        addRacers();
        addColliders();

        auto thWorld = std::static_pointer_cast<turbohiker::World> (world);

        auto& AI = turbohiker::GameAI::instantiateAI(thWorld);
        generateMap();

    }

    void Game::addRacers() {
        auto firstRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        firstRacer->setPosition( {-2.5, -2.0} );
        auto secondRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        secondRacer->setPosition( {-1.5, -2.0} );
        auto thirdRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        thirdRacer->setPosition( {-0.5, -2.0} );
        auto forthRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        forthRacer->setPosition( {0.5, -2.0} );
        auto fifthRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        fifthRacer->setPosition( {1.5, -2.0} );

        std::shared_ptr<turbohiker::Observer> firstObserver = std::make_shared<turbohiker::ScoreObserver> ( );
        leaderBoard.addObserver("CPU0", firstObserver);
        firstRacer->addObserver(firstObserver);

        std::shared_ptr<turbohiker::Observer> secondObserver = std::make_shared<turbohiker::ScoreObserver> ( );
        leaderBoard.addObserver("CPU1", secondObserver);
        secondRacer->addObserver(secondObserver);

        std::shared_ptr<turbohiker::Observer> thirdObserver = std::make_shared<turbohiker::ScoreObserver> ( );
        leaderBoard.addObserver("CPU2", thirdObserver);
        thirdRacer->addObserver(thirdObserver);

        std::shared_ptr<turbohiker::Observer> forthObserver = std::make_shared<turbohiker::ScoreObserver> ( );
        leaderBoard.addObserver("CPU3", forthObserver);
        forthRacer->addObserver(forthObserver);

        std::shared_ptr<turbohiker::Observer> fifthObserver = std::make_shared<turbohiker::ScoreObserver> ( );
        leaderBoard.addObserver("CPU4", fifthObserver);
        fifthRacer->addObserver(fifthObserver);

        world->addEntity(std::move(firstRacer));
        world->addEntity(std::move(secondRacer));
        world->addEntity(std::move(thirdRacer));
        world->addEntity(std::move(forthRacer));
        world->addEntity(std::move(fifthRacer));

    }

    void Game::addColliders() {
        auto bottomCollider = EntityRef (new TileEntity(window, {0.0, -3}, {8, 0.25},
                                                        nullptr, {0, 0}));

        auto topCollider = EntityRef (new TileEntity(window, {0.0, 3}, {8, 0.50},
                                                     nullptr, {0, 0}));


        auto rightCollider = EntityRef (new TileEntity(window, { 4.25, 0}, {1.0, 8},
                                                       nullptr, {0, 0}));

        auto leftCollider = EntityRef (new TileEntity(window, { -4.25, 0}, {1.0, 8},
                                                      nullptr, {0, 0}));
        world->addEntity(std::move(bottomCollider));
        world->addEntity(std::move(topCollider));
        world->addEntity(std::move(leftCollider));
        world->addEntity(std::move(rightCollider));
    }

    void Game::generateMap() {
        std::string tileSetPath = config["World"]["TileSet"].as_string_or_die();
        tileSet = std::make_shared<sf::Texture> (  );
        if (!tileSet->loadFromFile(tileSetPath))
            std::cerr << "Cannot load tile set " << tileSetPath << ". Please check the configuration file." << std::endl;


        double y = -2.75;
        generateStrip({3, 4}, {1, 3}, {4, 4}, y);

        for (uint8_t i = 0; i < 12; i++) {
            y += 0.5;
            generateStrip({2, 4}, {11, 4}, {0, 4}, y);
        }

    }

    void Game::generateStrip(sf::Vector2u Left, sf::Vector2u Middle, sf::Vector2u Right, double y) {
        double x = -3.75;
        world->addTile(EntityRef(new TileEntity(window, {x, y}, {0.50, 0.50}, tileSet, Left)));
        for (uint8_t j = 0; j < 14; j++) {
            x += 0.5;
            world->addTile(EntityRef(new TileEntity(window, {x, y}, {0.50, 0.50}, tileSet, Middle)));
        }
        x += 0.5;
        world->addTile(EntityRef(new TileEntity(window, {x, y}, {0.50, 0.50}, tileSet, Right)));

    }

    void Game::correctOutOfBounds() {
        float yBottom = gameView.getCenter().y + window->getSize().y / 2.0f;
        float yTop = gameView.getCenter().y - window->getSize().y / 2.0f;

        double yCoordB = Transformation::convertPosFromPixels(*window, {0, yBottom}).second;

        world->removeObstacles(yCoordB - 5.0);

        for (auto& ent : world->getEntities()) {
            if (ent->getType() != turbohiker::EntityType::Player && ent->getType() != turbohiker::EntityType::RacingHiker) continue;
            auto entPos = ent->getPosition();
            if (ent->getPosition().second < yCoordB) {
                std::cout << "Game Over!" << entPos.first << ", " << entPos.second << std::endl;
                ent->setVelocity( {0.0, 0.0} );
                ent->setPosition( {entPos.first, yCoordB + 0.5} );
            }
        }
    }

    void Game::spawnObstacle() {
        auto playerY = world->getPlayerPosition().second;

        {
            auto obstacleEntity = entFactory->createEntity(turbohiker::EntityType::StaticHikerActive);
            auto tmp = dynamic_cast<PassingHiker1 *> (obstacleEntity.release());
            tmp->spawn(playerY);
            obstacleEntity.reset(tmp);
            world->addEntity(std::move(obstacleEntity));
        }

        {
            auto movingObstacle = entFactory->createEntity(turbohiker::EntityType::MovingHikerActive);
            auto tmp = dynamic_cast<PassingHiker2 *> (movingObstacle.release());
            tmp->spawn(playerY);
            movingObstacle.reset(tmp);
            world->addEntity(std::move(movingObstacle));
        }
    }

    void Game::spawnFinishLine() {
        std::cerr << "Spawned finish line " << std::endl;

        if (finishDrawn) {
            for (uint8_t i = 0; i < 11; i++) {
                lastDrawnY += 0.5;
                generateStrip({2, 4}, {11, 4}, {0, 4}, lastDrawnY);
            }

            world->clearEntitiesAbove(lastDrawnY);

            {
                lastDrawnY += 0.5;
                generateStrip({3, 3}, {1, 5}, {4, 3}, lastDrawnY);

                lastDrawnY += 0.5;
                generateStrip({6, 4}, {6, 4}, {6, 4}, lastDrawnY);
                generateStrip({11, 0}, {11, 0}, {11, 0}, lastDrawnY);

                // Finish collider
                auto finishCollider = EntityRef ( new TileEntity (window, { 0.0, lastDrawnY + 5.5}, {8.0, 10.0},
                                                                  nullptr, {0, 0}, true) );

                world->addEntity(std::move(finishCollider));
                finishLine = lastDrawnY;

                std::cout << "PlayerY " << world->getPlayerPosition().second << "\t lastDrawnY " << lastDrawnY << std::endl;

                lastDrawnY += 0.5;
                generateStrip({6, 3}, {6, 3}, {6, 3}, lastDrawnY);
            }

            for (uint8_t i = 0; i < 11; i++) {
                lastDrawnY += 0.5;
                generateStrip({1, 2}, {1, 2}, {1, 2}, lastDrawnY);
            }

            lastDrawnY += 25;
        }
    }

    void Game::tryToDraw() {
        float topPixelY = gameView.getCenter().y - (gameView.getSize().y / 2);
        auto worldPos = Transformation::convertPosFromPixels(*window, {0, topPixelY});

        if (lastDrawnY < worldPos.second) {
            lastDrawnY += 0.5;
            generateStrip({2, 4}, {11, 4}, {0, 4}, lastDrawnY);
        }

    }

    void Game::displayScore() {
        sf::Vector2f viewCenter = gameView.getCenter();
        sf::Vector2f viewSize = gameView.getSize();
        playerScore.setPosition(viewCenter - (viewSize / 2.0f) + sf::Vector2f(10, 10) );
        playerScore.setString("Score: " + std::to_string(leaderBoard.getScore(playerName)) );
        window->draw(playerScore);
    }

    void Game::run() {
        using clock = std::chrono::high_resolution_clock;


        double timer = 0.0;
        double finishTimer = 0.0;
        double updateTimer = 0.0;
        const double fixedDelta = 1.0/75.0;


        float dTime;
        auto last = clock::now();
        sf::Event ev{};
        bool spawn = true;

        timeToFinish += turbohiker::Random::randFloat(-5.f, 10.f);
        while (window->isOpen()) {
            while (window->pollEvent(ev)) {
                if (ev.type == sf::Event::Closed) {
                    window->close();
                }
                if (gameFinished) continue;
                world->handleGameEvent(ev);
            }
            if (gameFinished) continue;


            auto now = clock::now();
            dTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - last).count();
            last = now;
            timer += dTime;
            updateTimer += dTime;
            finishTimer += dTime;

            if (timer >= 1.0) {
                timer = 0;
                if (spawn)
                    spawnObstacle();
            }

            if (timeToFinish > -1.0 && finishTimer >= timeToFinish) {
                timeToFinish = -1.0;
                finishDrawn = true;
                spawnFinishLine();
                spawn = false;
            }

            while (updateTimer >= fixedDelta) {
                world->update(float(fixedDelta));
                world->doTypeSpecificAction();
                if (!finishDrawn)
                    tryToDraw();

                if (finishDrawn && !gameFinished){
                    gameFinished = world->checkForFinish(finishLine);
                }
                correctOutOfBounds();
                calculateView(float(fixedDelta));

                updateTimer -= fixedDelta;

            }

            window->clear(sf::Color::Magenta);
            window->setView(gameView);
            if (gameFinished) {
                world->display();
                leaderBoard.display(playerName);
            }
            else {
                world->display();
                displayScore();
            }
            window->display();
        }
    }

    void Game::calculateView(float dTime) {
        float convertedFinish = Transformation::convertPosToPixels( *window, {0.0, finishLine + 2.5} ).y;
        if (finishLine <= 0.0 || gameView.getCenter().y > convertedFinish) {
            gameView.move(0, -world->getSpeed() * dTime);
        } else {
            world->setSpeed( 0.f );
        }
    }
}
