#include "../assertion.h"
#include "Game.h"
#include "PassingHiker1.h"
#include "TileEntity.h"
#include "Transformation.h"
#include <chrono>
#include <fstream>

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



        if (fullscreen) {
            window = std::make_shared<sf::RenderWindow> (sf::VideoMode(width, height), "TurboHiker",
                                                         sf::Style::Fullscreen);
        }
        else {
            window = std::make_shared<sf::RenderWindow> (sf::VideoMode(width, height), "TurboHiker",
                          sf::Style::Close | sf::Style::Titlebar);

        }

        window->setVerticalSyncEnabled(true);

        this->init();
    }

    void Game::init() {

        entFactory = FactoryCreator::getFactory("entity", window, config);

        EntityRef worldEnt = entFactory->createEntity(turbohiker::EntityType::World);
        if (worldEnt->getType() != turbohiker::EntityType::World)
            std::cerr << "Factory did not return a World entity." << std::endl;

        auto temp = dynamic_cast<World*> (worldEnt.get());
        ASSERT(temp != nullptr, "World pointer is not a valid World object.")
        worldEnt.release();
        world.reset(temp);

        world->addEntity(entFactory->createEntity(turbohiker::EntityType::Player));

        gameView.setSize(static_cast<sf::Vector2f> (window->getSize()));
        gameView.setCenter(static_cast<sf::Vector2f> (window->getSize()) / 2.0f);

        // Invisible collider at bottom of map
        std::string tileSetPath = config["World"]["Transparent"].as_string_or_die();
        auto transparent = std::make_shared<sf::Texture> (  );
        if (!transparent->loadFromFile(tileSetPath))
            std::cerr << "Cannot load transparent texture " << tileSetPath << ". Please check the configuration file." << std::endl;

        auto bottomCollider = EntityRef (new TileEntity(window, {0.0, -3}, {8, 0.25},
                                                        nullptr, {0, 0}));

        auto topCollider = EntityRef (new TileEntity(window, {0.0, 3}, {8, 0.50},
                                  nullptr, {0, 0}));


        auto rightCollider = EntityRef (new TileEntity(window, { 4, 0}, {0.5, 8},
                                                      nullptr, {0, 0}));

        auto leftCollider = EntityRef (new TileEntity(window, { -4, 0}, {0.5, 8},
                                                      nullptr, {0, 0}));
        world->addEntity(std::move(bottomCollider));
        world->addEntity(std::move(topCollider));
        world->addEntity(std::move(leftCollider));
        world->addEntity(std::move(rightCollider));


        generateMap();

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

    void Game::calculateView(float dTime) {
        float yBottom = gameView.getCenter().y + window->getSize().y / 2.0f;
        float yTop = gameView.getCenter().y - window->getSize().y / 2.0f;

        double yCoordB = Transformation::convertPosFromPixels(*window, {0, yBottom}).second;
        double yCoordT = Transformation::convertPosFromPixels(*window, {0, yTop}).second;
        
        world->removeObstacles(yCoordB - 5.0);

        if (world->getPlayerPosition().second < yCoordB || world->getPlayerPosition().second > yCoordT) {
            std::cout << "Game Over!" << world->getPlayerPosition().first << ", " << world->getPlayerPosition().second << std::endl;
            world->movePlayer( { 0.0, 0.5 } );
        }

        gameView.move(0, -world->getSpeed() * dTime);

    }

    void Game::spawnObstacle() {
        auto obstacleEntity = entFactory->createEntity(turbohiker::EntityType::StaticHikerActive);
        auto tmp = dynamic_cast<PassingHiker1*> (obstacleEntity.release());
        tmp->spawn(world->getPlayerPosition().second);
        obstacleEntity.reset(tmp);

        world->addEntity(std::move(obstacleEntity));
    }

    void Game::tryToDraw() {
        float topPixelY = gameView.getCenter().y - (gameView.getSize().y / 2);
        auto worldPos = Transformation::convertPosFromPixels(*window, {0, topPixelY});

        if (lastDrawnY < worldPos.second) {
            lastDrawnY += 0.5;
            generateStrip({2, 4}, {11, 4}, {0, 4}, lastDrawnY);
        }
    }

    void Game::run() {
        static double timer = 0.0;
        using clock = std::chrono::high_resolution_clock;
        float dTime;
        auto last = clock::now();
        sf::Event ev{};

        while (window->isOpen()) {
            while (window->pollEvent(ev)) {
                if (ev.type == sf::Event::Closed) {
                    window->close();
                }
                world->handleGameEvent(ev);
            }

            auto now = clock::now();
            dTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - last).count();
            last = now;
            timer += dTime;

            if (timer >= 1.0) {
                timer = 0;
                spawnObstacle();
            }

            window->clear(sf::Color::Magenta);
            world->update(dTime);
            world->doTypeSpecificAction();
            tryToDraw();
            calculateView(dTime);
            window->setView(gameView);
            world->display();
            window->display();
        }
    }
}
