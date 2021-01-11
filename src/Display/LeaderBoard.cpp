#include "LeaderBoard.h"
#include "Transformation.h"
#include <sstream>
#include <iomanip>

namespace turbohikerSFML {


    void LeaderBoard::init(std::shared_ptr<sf::RenderWindow> &window, const sf::Font &userFont, std::string texturePath) {
        _window = window;
        windowScalar = _window->getSize().x < _window->getSize().y ? _window->getSize().x : _window->getSize().y;

        if ( !lbTexture.loadFromFile(texturePath) ) {
            std::cerr << "Could not load leaderboard texture " + texturePath + ". Please check the configuration file." << std::endl;
            lbShape.setFillColor(sf::Color(0, 0, 0, 150));
        } else {
            lbShape.setTexture(&lbTexture);
        }

        lbShape.setSize( Transformation::convertSizeToPixels( *_window, {3.5, 3.25}) );
        lbShape.setOrigin(lbShape.getSize() / 2.0f);

        title.setFont(userFont);
        title.setCharacterSize(static_cast<uint32_t> (windowScalar / 20.0f));
        title.setFillColor(sf::Color::White);
        title.setOutlineColor(sf::Color::Black);
        title.setOutlineThickness(windowScalar / 384.0f);
        title.setString("-==Leaderboard==-");
        auto titleBounds = title.getGlobalBounds();
        title.setOrigin( titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);


        scores.setFont(userFont);
        scores.setCharacterSize(static_cast<uint32_t> (windowScalar / 32.0f));
//        scores.setCharacterSize(40);
        scores.setFillColor(sf::Color::White);
        scores.setOutlineColor(sf::Color::Black);
        scores.setOutlineThickness(windowScalar / 640.0f);

        personalBest.setFont(userFont);
        personalBest.setCharacterSize(static_cast<uint32_t> (windowScalar / 20.0f));
//        personalBest.setCharacterSize(50);
        personalBest.setFillColor(sf::Color::Yellow);
        personalBest.setOutlineColor(sf::Color::Black);
        personalBest.setOutlineThickness(windowScalar / 640.0f);

    }

    void LeaderBoard::display(std::string &playerName) {
        auto lbPosition = _window->getView().getCenter() - Transformation::convertSizeToPixels( *_window, {0,1});
        lbShape.setPosition( lbPosition );
        _window->draw(lbShape);
        title.setPosition({lbPosition.x, lbPosition.y - lbShape.getSize().y * 0.25f});
        _window->draw(title);

        std::stringstream scoreStream;
        std::map<int, std::string> scoreMap;
        for ( auto observer : getScoreObserverMap() ) {
            std::string name = observer.first;
            scoreMap[getScore(name)] = name;
        }

        for (auto it = scoreMap.rbegin(); it != scoreMap.rend(); ++it ) {
            scoreStream << std::left << std::setw(15)
                        << (*it).second
                        << std::right << std::setw(15)
                        << (*it).first << std::endl;
        }


        scores.setString(scoreStream.str());
        auto scoreBounds = scores.getGlobalBounds();
        scores.setOrigin( scoreBounds.left + scoreBounds.width / 2.0f, scoreBounds.top + scoreBounds.height / 2.0f);
        scores.setPosition( {lbPosition.x, lbPosition.y + (lbShape.getSize().y * 0.025f)} );
        _window->draw(scores);

        saveHighScore(playerName);
        std::string highScoreStr = "Personal best: " + std::to_string(getHighScore(playerName));
        personalBest.setString(highScoreStr);
        auto pbBounds = personalBest.getGlobalBounds();
        personalBest.setOrigin( pbBounds.left + pbBounds.width / 2.0f, pbBounds.top + pbBounds.height / 2.0f);
        personalBest.setPosition({lbPosition.x, lbPosition.y + (lbShape.getSize().y * 0.25f)});
        _window->draw(personalBest);

    }

}