#pragma once
#include "Observer.h"
#include <iostream>
#include <ostream>
#include <fstream>
#include <map>
#include <memory>


namespace turbohiker {

    class LeaderBoard {
    public:
        LeaderBoard() = default;
        virtual ~LeaderBoard() = default;

        void printLeaderBoard(std::ostream& out = std::cout);
        void addObserver(std::string observername, std::shared_ptr<Observer> observer);

        const std::map<std::string, std::shared_ptr<Observer>> &getScoreObserverMap() const;

        int getScore(std::string &name) const;

        void saveHighScore(std::string& playerName) const;

        int getHighScore(const std::string& playerName) const;

    private:
        std::map<std::string, std::shared_ptr<Observer>> scoreObserverMap;
    };

}
