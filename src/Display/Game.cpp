#include "../assertion.h"
#include "Game.h"
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
            window.create(sf::VideoMode(width, height), "TurboHiker",
                          sf::Style::Fullscreen);
        }
        else {
            window.create(sf::VideoMode(width, height), "TurboHiker",
                          sf::Style::Close | sf::Style::Titlebar);

        }

        window.setVerticalSyncEnabled(false);

        sharedWindow = std::shared_ptr<sf::RenderWindow> (&window);
//        weakPtrWindow = sharedWindow;

        this->init();
    }

    void Game::init() {

        auto windowPtr = std::shared_ptr<sf::RenderWindow>(&window);
        entFactory = FactoryCreator::getFactory("entity", windowPtr, config);

        EntityRef worldEnt = entFactory->createEntity(turbohiker::EntityType::World);
        if (worldEnt->getType() != turbohiker::EntityType::World)
            std::cerr << "Factory did not return a World entity." << std::endl;

        auto temp = dynamic_cast<World*> (worldEnt.get());
        ASSERT(temp != nullptr, "World pointer is not a valid World object.")
        worldEnt.release();
        world.reset(temp);

        world->addEntity(entFactory->createEntity(turbohiker::EntityType::Player));

        gameView.setSize(static_cast<sf::Vector2f> (window.getSize()));
        gameView.setCenter(static_cast<sf::Vector2f> (window.getSize()) / 2.0f);

        // Invisible collider at bottom of map
        std::string tileSetPath = config["World"]["Transparent"].as_string_or_die();
        auto transparent = std::make_shared<sf::Texture> (  );
        if (!transparent->loadFromFile(tileSetPath))
            std::cerr << "Cannot load transparent texture " << tileSetPath << ". Please check the configuration file." << std::endl;


        world->addEntity(EntityRef (new TileEntity(sharedWindow, {0.0, -3.75}, {8, 1},
                                                 transparent, {0, 0})));
        world->addEntity(EntityRef (new TileEntity(sharedWindow, {0.0, 3.25}, {8, 1},
                                                   transparent, {0, 0})));

        generateMap();

    }

    void Game::generateMap() {
        std::string tileSetPath = config["World"]["TileSet"].as_string_or_die();
        tileSet = std::make_shared<sf::Texture> (  );
        if (!tileSet->loadFromFile(tileSetPath))
            std::cerr << "Cannot load tile set " << tileSetPath << ". Please check the configuration file." << std::endl;


        double y = -3.0;
        generateStrip({3, 4}, {1, 3}, {4, 4}, y);

        for (uint8_t i = 0; i < 12; i++) {
            y += 0.5;
            generateStrip({2, 4}, {11, 4}, {0, 4}, y);
        }

//        generateStrip({3, 3}, {1, 5}, {4, 3}, y + 0.5);



    }

    void Game::generateStrip(sf::Vector2u Left, sf::Vector2u Middle, sf::Vector2u Right, double y) {
        double x = -4.0;
        world->addTile(EntityRef(new TileEntity(sharedWindow, {x, y}, {0.50, 0.50}, tileSet, Left)));
        for (uint8_t j = 0; j < 14; j++) {
            x += 0.5;
            world->addTile(EntityRef(new TileEntity(sharedWindow, {x, y}, {0.50, 0.50}, tileSet, Middle)));
        }
        x += 0.5;
        world->addTile(EntityRef(new TileEntity(sharedWindow, {x, y}, {0.50, 0.50}, tileSet, Right)));

    }

    void Game::calculateView() {
//        sf::Vector2f playerPos = Transformation::convertPosToPixels(window, world->getPlayerPosition());
//        float topPixelY = gameView.getCenter().y - (gameView.getSize().y / 2);
//        auto pVelocity = Transformation::convertSizeToPixels(window, world->getPlayerVelocity());
//        auto pSize = Transformation::convertSizeToPixels(window, world->getPlayerSize());

        gameView.move(0, -world->getSpeed());


    }

    void Game::tryToDraw() {
        float topPixelY = gameView.getCenter().y - (gameView.getSize().y / 2);
        auto worldPos = Transformation::convertPosFromPixels(window, {0, topPixelY});

        if (lastDrawnY < worldPos.second) {
            lastDrawnY += 0.5;
            generateStrip({2, 4}, {11, 4}, {0, 4}, lastDrawnY);
        }
    }

    void Game::run() {
        using clock = std::chrono::high_resolution_clock;
        float dTime;
        auto last = clock::now();
        sf::Event ev{};

        while (window.isOpen()) {
            while (window.pollEvent(ev))
                if (ev.type == sf::Event::Closed) window.close();

            auto now = clock::now();
            dTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - last).count();
            last = now;

            window.clear(sf::Color(150, 150, 150));
            world->update(dTime);
            world->doTypeSpecificAction();
            window.setView(gameView);
            tryToDraw();
            gameView.move(0, -world->getSpeed());
            world->display();
            window.display();
        }
    }
}
