#include "ScoreObserver.h"


namespace turbohiker {

    void ScoreObserver::onNotify(ObservableEvent event) {
        switch (event) {
            case ObservableEvent::None:
                break;
            case ObservableEvent::Collision:
                score -= 35;
                break;
            case ObservableEvent::FinishedFirst:
                score += 350;
                break;
            case ObservableEvent::FinishedSecond:
                score += 275;
                break;
            case ObservableEvent::FinishedThird:
                score += 200;
                break;
            case ObservableEvent::FinishedForth:
                score += 125;
                break;
            case ObservableEvent::FinishedFifth:
                score += 50;
                break;
            case ObservableEvent::FinishedSixth:
                score += 5;
                break;
            case ObservableEvent::Yelled:
                score -= 15;
                break;
        }

    }



    std::ostream &operator<<(std::ostream &out, const ScoreObserver& so) {
        out << so.score;
        return out;
    }

}
