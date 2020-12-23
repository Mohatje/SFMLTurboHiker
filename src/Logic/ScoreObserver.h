#pragma once
#include "Observer.h"


namespace turbohiker {

    class ScoreObserver : public Observer {
    public:

        void onNotify(ObservableEvent event) override;
        std::ostream &operator<<(std::ostream& out) const override;


    private:
        int score = 0;
    };

}
