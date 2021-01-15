#pragma once
#include "Observer.h"


namespace turbohiker {

    class ScoreObserver : public Observer {
    public:
        void onNotify(ObservableEvent event) override;

        /**
         * Method to get the score value of the ScoreObserver
         * @return score of the observed entity
         */
        int getValue() override;
    private:
        int score = 0;
        bool finished = false;
    };

}
