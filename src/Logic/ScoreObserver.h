#pragma once
#include "Observer.h"


namespace turbohiker {

    class ScoreObserver : public Observer {
    public:

        void onNotify(ObservableEvent event) override;
        friend std::ostream &operator<<(std::ostream& out, const ScoreObserver& so);


    private:
        int score = 0;
        bool finished = false;
    };

}
