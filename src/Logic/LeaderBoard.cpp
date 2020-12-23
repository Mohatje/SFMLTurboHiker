#include "LeaderBoard.h"
#include "ScoreObserver.h"
#include <sstream>


namespace turbohiker {

    void LeaderBoard::addObserver(std::string observername, std::shared_ptr<Observer> observer) {
        scoreObserverMap[observername] = observer;
    }

    void LeaderBoard::printLeaderBoard(std::ostream &out) {
//        out << "----------Leaderboard----------" << std::endl;
        for (auto& scorePair : scoreObserverMap) {
            out << scorePair.first << ": " << *dynamic_cast<ScoreObserver*> (scorePair.second.get()) << std::endl;
        }
        out << std::endl;
    }

    const std::map<std::string, std::shared_ptr<Observer>> &LeaderBoard::getScoreObserverMap() const {
        return scoreObserverMap;
    }

    int LeaderBoard::getScore(std::string &name) const {
        std::stringstream sStream;
        sStream << *dynamic_cast<ScoreObserver*> (scoreObserverMap.at(name).get());
        return std::stoi(sStream.str());
    }

    void LeaderBoard::saveHighScore(std::string& playerName) const {
        int curScore = getScore(playerName);
        std::fstream highScoreFile;

        int highScore = getHighScore(playerName);
        if (highScore < curScore) {
            highScoreFile.clear();
            highScoreFile.close();
            highScoreFile.open(playerName + ".save", std::ios::trunc);
            highScoreFile.close();
            highScoreFile.open(playerName + ".save");
            highScoreFile << curScore;
        }
        highScoreFile.close();
        std::cout << highScore << "\t" << curScore << std::endl;
    }

    int LeaderBoard::getHighScore(const std::string& playerName) const {
        std::fstream highScoreFile(playerName + ".save");
        if ( !highScoreFile.is_open() )
            std::cerr << "Failed to open save file. Highscore is reset." << std::endl;

        std::string scoreStr;
        getline(highScoreFile, scoreStr);

        return scoreStr.empty() ? 0 : std::stoi(scoreStr);
    }
}