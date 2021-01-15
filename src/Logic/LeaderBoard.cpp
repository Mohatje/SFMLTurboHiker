#include "LeaderBoard.h"
#include "ScoreObserver.h"
#include <sstream>

namespace turbohiker {

void LeaderBoard::addObserver(std::string observername, std::shared_ptr<Observer> observer)
{
        scoreObserverMap[observername] = observer;
}

void LeaderBoard::printLeaderBoard(std::ostream& out)
{
        // ASCII Leaderboard output
        out << "----------Leaderboard----------" << std::endl;
        for (auto& scorePair : scoreObserverMap) {
                out << scorePair.first << ": " << scorePair.second->getValue() << std::endl;
        }
        out << std::endl;
}

const std::map<std::string, std::shared_ptr<Observer>>& LeaderBoard::getScoreObserverMap() const
{
        return scoreObserverMap;
}

int LeaderBoard::getScore(std::string& name) const { return scoreObserverMap.at(name)->getValue(); }

void LeaderBoard::saveHighScore(std::string& playerName) const
{
        // Save current score to file if it's higher than the old highscore (begins at 0)
        // Imagine having highscore that is negative smh
        int curScore = getScore(playerName);
        std::ofstream highScoreFile;

        int highScore = getHighScore(playerName);
        if (highScore < curScore) {
                highScoreFile.open(playerName + ".save");
                highScoreFile << curScore;
        }
        highScoreFile.close();
}

int LeaderBoard::getHighScore(const std::string& playerName) const
{
        // Read highscore from file,
        // if file doesn't exist create it and return 0
        std::fstream highScoreFile(playerName + ".save");
        if (!highScoreFile.is_open()) {
                std::cerr << "Failed to open save file. Creating new file." << std::endl;
                highScoreFile.open(playerName + ".save", std::ios::out);
        }

        std::string scoreStr;
        getline(highScoreFile, scoreStr);
        highScoreFile.close();
        return scoreStr.empty() ? 0 : std::stoi(scoreStr);
}
} // namespace turbohiker