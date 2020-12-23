#include "LeaderBoard.h"
#include "Transformation.h"
#include <sstream>
#include <iomanip>

namespace turbohikerSFML {


    void LeaderBoard::init(std::shared_ptr<sf::RenderWindow> &window, const sf::Font &userFont) {
        _window = window;
        lbShape.setFillColor(sf::Color(0, 0, 0, 150));
        lbShape.setSize( Transformation::convertSizeToPixels( *_window, {2.5, 2.5}) );
        lbShape.setOrigin(lbShape.getSize() / 2.0f);

        title.setFont(userFont);
        title.setCharacterSize(50);
        title.setFillColor(sf::Color::White);
        title.setOutlineColor(sf::Color::Black);
        title.setOutlineThickness(2.5f);
        title.setString("-==Leaderboard==-");
        auto titleBounds = title.getGlobalBounds();
        title.setOrigin( titleBounds.left + titleBounds.width / 2.0f, titleBounds.top + titleBounds.height / 2.0f);


        scores.setFont(userFont);
        scores.setCharacterSize(30);
        scores.setFillColor(sf::Color::White);
        scores.setOutlineColor(sf::Color::Black);
        scores.setOutlineThickness(1.5f);

        personalBest.setFont(userFont);
        personalBest.setCharacterSize(40);
        personalBest.setFillColor(sf::Color::Yellow);
        personalBest.setOutlineColor(sf::Color::Black);
        personalBest.setOutlineThickness(1.5f);

    }

    void LeaderBoard::display(std::string &playerName) {
        auto lbPosition = _window->getView().getCenter() - Transformation::convertSizeToPixels( *_window, {0,1});
        lbShape.setPosition( lbPosition );
        _window->draw(lbShape);
        title.setPosition({lbPosition.x, lbPosition.y - lbShape.getSize().y * 0.40f});
        _window->draw(title);

        std::stringstream scoreStream;
        std::map<int, std::string> scoreMap;
        for ( auto observer : getScoreObserverMap() ) {
            std::string name = observer.first;
            scoreMap[getScore(name)] = name;
        }

        for (auto it = scoreMap.rbegin(); it != scoreMap.rend(); ++it ) {
            scoreStream << std::setw(15);
            scoreStream << std::left << (*it).second;
            scoreStream << std::setw(15);
            scoreStream << std::right << (*it).first << std::endl;
        }


        scores.setString(scoreStream.str());
        auto scoreBounds = scores.getGlobalBounds();
        scores.setOrigin( scoreBounds.left + scoreBounds.width / 2.0f, scoreBounds.top + scoreBounds.height / 2.0f);
        scores.setPosition( {lbPosition.x, lbPosition.y} );
        _window->draw(scores);

        saveHighScore(playerName);
        std::string highScoreStr = "Personal best: " + std::to_string(getHighScore(playerName));
        personalBest.setString(highScoreStr);
        auto pbBounds = personalBest.getGlobalBounds();
        personalBest.setOrigin( pbBounds.left + pbBounds.width / 2.0f, pbBounds.top + pbBounds.height / 2.0f);
        personalBest.setPosition({lbPosition.x, lbPosition.y + (lbShape.getSize().y * 0.35f)});
        _window->draw(personalBest);





    }

}