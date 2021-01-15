#include "Game.h"
#include "../Logic/Random.h"
#include "../Logic/ScoreObserver.h"
#include "../assertion.h"
#include "PassingHiker1.h"
#include "PassingHiker2.h"
#include "TileEntity.h"
#include "Transformation.h"
#include <chrono>

namespace turbohikerSFML {
Game::Game() : Game("./Config/config.ini") {}

Game::Game(const std::string& configPath)
{

        // Load config file
        try {
                std::ifstream config_in(configPath);
                config_in >> config;
        } catch (ini::ParseException& ex) {
                std::cerr << "Error parsing file: " << configPath << ": " << ex.what() << std::endl;
        }

        // Load window properties
        int width = config["Window"]["Width"].as_int_or_default(1280);
        int height = config["Window"]["Height"].as_int_or_default(720);
        bool vsync = config["Window"]["VSync"].as_bool_or_default(false);
        bool fullscreen = config["Window"]["Fullscreen"].as_bool_or_default(false);

        // Load font
        std::string fontPath = config["Settings"]["FontPath"].as_string_or_die();
        if (!gameFont.loadFromFile(fontPath))
                std::cerr << "Could not load font " + fontPath + " . Please check the configuration file" << std::endl;

        // create window
        if (fullscreen) {
                window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "TurboHiker",
                                                            sf::Style::Fullscreen);
        } else {
                window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "TurboHiker",
                                                            sf::Style::Close | sf::Style::Titlebar);
        }
        window->setVerticalSyncEnabled(vsync);

        std::string lbTexPath = config["Settings"]["LeaderboardTexture"].as_string_or_die();
        leaderBoard.init(window, gameFont, lbTexPath);

        this->init();
}

void Game::init()
{

        // truncate playername if it's more than 12 chars
        playerName = config["Settings"]["PlayerName"].as_string_or_default("Player");
        if (playerName.size() > 12)
                playerName = playerName.substr(0, 12);

        // get a windowScalar to keep the text consistent across other resolutions
        float windowScalar = window->getSize().x < window->getSize().y ? window->getSize().x : window->getSize().y;

        // Ready the score display
        playerScore.setFont(gameFont);
        playerScore.setCharacterSize(static_cast<uint32_t>(windowScalar / 21.f));
        playerScore.setFillColor(sf::Color::White);
        playerScore.setOutlineColor(sf::Color::Black);
        playerScore.setOutlineThickness(windowScalar / 384.f);

        // create an entity factory & world
        entFactory = FactoryCreator::getFactory("entity", window, config);
        EntityRef worldEnt = entFactory->createEntity(turbohiker::EntityType::World);
        if (worldEnt->getType() != turbohiker::EntityType::World)
                std::cerr << "Factory did not return a World entity." << std::endl;

        // Dynamic cast world entity to world class object, this way we can use world
        // specific methods this conversion happens only once so no noticeable
        // performance hit
        auto temp = dynamic_cast<World*>(worldEnt.release());
        ASSERT(temp != nullptr, "World pointer is not a valid World object.")
        world.reset(temp);

        world->addEntity(entFactory->createEntity(turbohiker::EntityType::Player));
        std::shared_ptr<turbohiker::Observer> playerObserver = std::make_shared<turbohiker::ScoreObserver>();
        leaderBoard.addObserver(playerName, playerObserver);
        world->getPlayerPtr()->addObserver(std::move(playerObserver));

        gameView.setSize(static_cast<sf::Vector2f>(window->getSize()));
        gameView.setCenter(static_cast<sf::Vector2f>(window->getSize()) / 2.0f);

        addRacers();
        addColliders();

        auto thWorld = std::static_pointer_cast<turbohiker::World>(world);

        // instantiate ai
        auto& AI = turbohiker::GameAI::instantiateAI(thWorld);

        generateMap();

        std::string finishPortal = config["World"]["FinishPortal"].as_string_or_die();
        finishTexture = std::make_shared<sf::Texture>();
        if (!(finishTexture->loadFromFile(finishPortal)))
                std::cerr << "Finish portal texture could not be loaded. Check the "
                             "configuration file."
                          << std::endl;

        finishAnimation = std::unique_ptr<Animation>(new Animation(finishTexture, {5, 1}, 0.20f));
}

void Game::addRacers()
{
        // Add racers, their observers and names
        auto firstRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        firstRacer->setPosition({-2.5, -2.0});
        auto secondRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        secondRacer->setPosition({-1.0, -2.0});
        auto thirdRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        thirdRacer->setPosition({0.5, -2.0});
        auto forthRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        forthRacer->setPosition({2.0, -2.0});
        auto fifthRacer = entFactory->createEntity(turbohiker::EntityType::RacingHiker);
        fifthRacer->setPosition({3.5, -2.0});

        std::shared_ptr<turbohiker::Observer> firstObserver = std::make_shared<turbohiker::ScoreObserver>();
        leaderBoard.addObserver("CPU0", firstObserver);
        firstRacer->addObserver(firstObserver);

        std::shared_ptr<turbohiker::Observer> secondObserver = std::make_shared<turbohiker::ScoreObserver>();
        leaderBoard.addObserver("CPU1", secondObserver);
        secondRacer->addObserver(secondObserver);

        std::shared_ptr<turbohiker::Observer> thirdObserver = std::make_shared<turbohiker::ScoreObserver>();
        leaderBoard.addObserver("CPU2", thirdObserver);
        thirdRacer->addObserver(thirdObserver);

        std::shared_ptr<turbohiker::Observer> forthObserver = std::make_shared<turbohiker::ScoreObserver>();
        leaderBoard.addObserver("CPU3", forthObserver);
        forthRacer->addObserver(forthObserver);

        std::shared_ptr<turbohiker::Observer> fifthObserver = std::make_shared<turbohiker::ScoreObserver>();
        leaderBoard.addObserver("CPU4", fifthObserver);
        fifthRacer->addObserver(fifthObserver);

        world->addEntity(std::move(firstRacer));
        world->addEntity(std::move(secondRacer));
        world->addEntity(std::move(thirdRacer));
        world->addEntity(std::move(forthRacer));
        world->addEntity(std::move(fifthRacer));
}

void Game::addColliders()
{
        // Create the view colliders and add them to world
        auto bottomCollider = EntityRef(new TileEntity(window, {0.0, -3}, {8, 0.25}, nullptr, {0, 0}));

        auto topCollider = EntityRef(new TileEntity(window, {0.0, 3}, {8, 0.50}, nullptr, {0, 0}));

        auto rightCollider = EntityRef(new TileEntity(window, {4.25, 0}, {1.0, 8}, nullptr, {0, 0}));

        auto leftCollider = EntityRef(new TileEntity(window, {-4.25, 0}, {1.0, 8}, nullptr, {0, 0}));
        world->addEntity(std::move(bottomCollider));
        world->addEntity(std::move(topCollider));
        world->addEntity(std::move(leftCollider));
        world->addEntity(std::move(rightCollider));
}

void Game::generateMap()
{
        // Generate initial map
        std::string tileSetPath = config["World"]["TileSet"].as_string_or_die();
        tileSet = std::make_shared<sf::Texture>();
        if (!tileSet->loadFromFile(tileSetPath))
                std::cerr << "Cannot load tile set " << tileSetPath << ". Please check the configuration file."
                          << std::endl;

        double y = -2.75;
        generateStrip({3, 4}, {1, 3}, {4, 4}, y);

        for (uint8_t i = 0; i < 12; i++) {
                y += 0.5;
                generateStrip({2, 4}, {11, 4}, {0, 4}, y);
        }
}

void Game::generateStrip(sf::Vector2u Left, sf::Vector2u Middle, sf::Vector2u Right, double y)
{
        // Generate a horizontal `strip` of terrain, left middle and right are self
        // explanatory these are all coordinates in the tilemap
        double x = -3.75;
        world->addTile(EntityRef(new TileEntity(window, {x, y}, {0.50, 0.50}, tileSet, Left)));
        for (uint8_t j = 0; j < 14; j++) {
                x += 0.5;
                world->addTile(EntityRef(new TileEntity(window, {x, y}, {0.50, 0.50}, tileSet, Middle)));
        }
        x += 0.5;
        world->addTile(EntityRef(new TileEntity(window, {x, y}, {0.50, 0.50}, tileSet, Right)));
}

void Game::correctOutOfBounds()
{
        float yBottom = gameView.getCenter().y + window->getSize().y / 2.0f;
        float yTop = gameView.getCenter().y - window->getSize().y / 2.0f;

        double yCoordB = Transformation::convertPosFromPixels(*window, {0, yBottom}).second;

        world->removeObstacles(yCoordB - 5.0);

        for (auto& ent : world->getEntities()) {
                if (ent->getType() != turbohiker::EntityType::Player &&
                    ent->getType() != turbohiker::EntityType::RacingHiker)
                        continue;
                auto entPos = ent->getPosition();
                if (ent->getPosition().second < yCoordB) {
                        ent->setVelocity({0.0, 0.0});
                        ent->setPosition({entPos.first, yCoordB + 0.5});
                        // Hmm perhaps punish them for trying to get out of bounds/getting stuck ?
                }
        }
}

void Game::spawnObstacle()
{
        // Executed every second, spawns a moving and static obstacle
        auto playerY = world->getPlayerPosition().second;

        {
                auto obstacleEntity = entFactory->createEntity(turbohiker::EntityType::StaticHikerActive);
                auto tmp = dynamic_cast<PassingHiker1*>(obstacleEntity.release());
                tmp->spawn(playerY);
                obstacleEntity.reset(tmp);
                world->addEntity(std::move(obstacleEntity));
        }

        {
                auto movingObstacle = entFactory->createEntity(turbohiker::EntityType::MovingHikerActive);
                auto tmp = dynamic_cast<PassingHiker2*>(movingObstacle.release());
                tmp->spawn(playerY);
                movingObstacle.reset(tmp);
                world->addEntity(std::move(movingObstacle));
        }
}

void Game::spawnFinishLine()
{

        // Spawning the finish line and terrain
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
                        generateFinishPortals(lastDrawnY);

                        //                generateStrip({11, 0}, {11, 0}, {11, 0}, lastDrawnY);

                        // Finish collider
                        auto finishCollider = EntityRef(
                            new TileEntity(window, {0.0, lastDrawnY + 5.5}, {8.0, 10.0}, nullptr, {0, 0}, true));

                        world->addEntity(std::move(finishCollider));
                        finishLine = lastDrawnY;

                        std::cout << "PlayerY " << world->getPlayerPosition().second << "\t lastDrawnY " << lastDrawnY
                                  << std::endl;

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

void Game::tryToDraw()
{
        // attempt to generate a new terrain strip
        float topPixelY = gameView.getCenter().y - (gameView.getSize().y / 2);
        auto worldPos = Transformation::convertPosFromPixels(*window, {0, topPixelY});

        if (lastDrawnY < worldPos.second) {
                lastDrawnY += 0.5;
                generateStrip({2, 4}, {11, 4}, {0, 4}, lastDrawnY);
        }
}

void Game::displayScore()
{
        sf::Vector2f viewCenter = gameView.getCenter();
        sf::Vector2f viewSize = gameView.getSize();
        playerScore.setPosition(viewCenter - (viewSize / 2.0f) + sf::Vector2f(10, 10));
        playerScore.setString("Score: " + std::to_string(leaderBoard.getScore(playerName)));
        window->draw(playerScore);
}

void Game::run()
{
        using clock = std::chrono::high_resolution_clock;

        // declare timers
        double timer = 0.0;
        double finishTimer = 0.0;
        double updateTimer = 0.0;
        const double fixedDelta = 1.0 / 75.0;

        float dTime;
        auto last = clock::now();
        sf::Event ev{};
        bool spawn = true;

        timeToFinish += turbohiker::Random::randFloat(-5.f, 10.f);
        while (window->isOpen()) {
                // close event polling & world event polling
                while (window->pollEvent(ev)) {
                        if (ev.type == sf::Event::Closed) {
                                window->close();
                        }
                        if (gameFinished)
                                continue;
                        world->handleGameEvent(ev);
                }
                if (gameFinished) {
                        continue;
                }

                // update timers
                auto now = clock::now();
                dTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - last).count();
                last = now;
                timer += dTime;
                updateTimer += dTime;
                finishTimer += dTime;

                // obstacle & position timer
                while (timer >= 1.0) {
                        timer -= 1.0;
                        if (spawn)
                                spawnObstacle();

                        if (!gameFinished)
                                world->observeOrder();
                }

                // check if we should spawn the finish line
                if (timeToFinish > -1.0 && finishTimer >= timeToFinish) {
                        timeToFinish = -1.0;
                        finishDrawn = true;
                        spawnFinishLine();
                        spawn = false;
                }

                // Update world on a fixed delta
                while (updateTimer >= fixedDelta) {
                        world->update(float(fixedDelta));
                        world->doTypeSpecificAction();
                        if (!finishDrawn)
                                tryToDraw();

                        if (finishDrawn && !gameFinished) {
                                gameFinished = world->checkForFinish(finishLine);
                        }
                        correctOutOfBounds();
                        calculateView(float(fixedDelta));

                        updateTimer -= fixedDelta;
                }

                // draw elements to screen
                window->clear(sf::Color::Magenta);
                window->setView(gameView);
                finishAnimation->update(0, float(fixedDelta));
                world->displayTiles();
                for (auto& rect : finishPortals) {
                        rect.setTextureRect(finishAnimation->textureRect);
                        window->draw(rect);
                }
                world->displayEntities();

                if (gameFinished)
                        leaderBoard.display(playerName);
                else
                        displayScore();
                window->display();
        }
}

void Game::calculateView(float dTime)
{
        float convertedFinish = Transformation::convertPosToPixels(*window, {0.0, finishLine + 2.5}).y;
        if (finishLine <= 0.0 || gameView.getCenter().y > convertedFinish) {
                gameView.move(0, -world->getSpeed() * dTime);
        } else {
                world->setSpeed(0.f);
        }
}

void Game::generateFinishPortals(double _lastDrawnY)
{
        // generate finish portals
        double x = -3.50;
        for (int i = 0; i < 8; i++) {
                sf::RectangleShape tmp(Transformation::convertSizeToPixels(*window, {1.0, 1.0}));
                tmp.setOrigin(tmp.getSize() / 2.0f);
                tmp.setPosition(Transformation::convertPosToPixels(*window, {x, _lastDrawnY + 0.25}));
                tmp.setTexture(finishTexture.get());
                finishPortals.emplace_back(tmp);
                x += 1.0;
        }
}
} // namespace turbohikerSFML
