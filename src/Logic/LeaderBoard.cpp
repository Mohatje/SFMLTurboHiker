#include "LeaderBoard.h"
#include <sstream>


namespace turbohiker {

    void LeaderBoard::addObserver(std::string observername, std::shared_ptr<Observer> observer) {
        scoreObserverMap[observername] = observer;
    }

    void LeaderBoard::printLeaderBoard(std::ostream &out) {
        out << "----------Leaderboard----------" << std::endl;
        for (auto& scorePair : scoreObserverMap) {
            out << scorePair.first << ": "; scorePair.second->operator<<(out) << std::endl;
        }
        out << std::endl;
    }

    const std::map<std::string, std::shared_ptr<Observer>> &LeaderBoard::getScoreObserverMap() const {
        return scoreObserverMap;
    }

    int LeaderBoard::getScore(std::string name) const {
        std::stringstream sStream;
        scoreObserverMap.at(name)->operator<<(sStream);
        return std::stoi(sStream.str());
    }
}