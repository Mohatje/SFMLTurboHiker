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
        /**
         * Default constructor
         */
        LeaderBoard() = default;
        /**
         * Default destructor
         */
        virtual ~LeaderBoard() = default;

        /**
         * Method to print the Leaderboard values in ASCII format
         * @param out the output stream
         */
        void printLeaderBoard(std::ostream& out = std::cout);

        /**
         * Method to add observer to the observer list within the leaderboard.
         * @param observername name for the observer
         * @param observer observer object itself
         */
        void addObserver(std::string observername, std::shared_ptr<Observer> observer);

        /**
         * Getter for the score observers dictionary.
         * @return the dictionary in format {string: Observer}
         */
        const std::map<std::string, std::shared_ptr<Observer>> &getScoreObserverMap() const;

        /**
         * Getter for the score of a specific observer/hiker
         * @param name hiker name
         * @return the score for the chosen hiker, if they exist
         */
        int getScore(std::string &name) const;

        /**
         * Method which regulates the saving of highscores
         * @param playerName each player can have their highscore saved
         */
        void saveHighScore(std::string& playerName) const;

        /**
         * Getter for the highscore (all time high) of a specific player.\n
         * The score is loaded from disk
         * @param playerName self explanatory
         * @return the highscore of the chosen hiker if it has been saved beforehand, 0 if there's no HS on disk.
         */
        int getHighScore(const std::string& playerName) const;

    private:
        std::map<std::string, std::shared_ptr<Observer>> scoreObserverMap;
    };

}
