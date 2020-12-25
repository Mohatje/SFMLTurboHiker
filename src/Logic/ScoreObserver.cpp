#include "ScoreObserver.h"


namespace turbohiker {

    void ScoreObserver::onNotify(ObservableEvent event) {
        if (finished) return;

        switch (event) {
            case ObservableEvent::None:
                break;
            case ObservableEvent::FinishedFirst:
                score += 300;
                finished = true;
                break;
            case ObservableEvent::FinishedSecond:
                score += 275;
                finished = true;
                break;
            case ObservableEvent::FinishedThird:
                score += 200;
                finished = true;
                break;
            case ObservableEvent::FinishedForth:
                score += 125;
                finished = true;
                break;
            case ObservableEvent::FinishedFifth:
                score += 50;
                finished = true;
                break;
            case ObservableEvent::FinishedSixth:
                score += 5;
                finished = true;
                break;
            case ObservableEvent::Collision:
                score -= 10;
                break;
            case ObservableEvent::Yelled:
                score -= 5;
                break;
            case ObservableEvent::WorldSpeed:
                score += 5;
                break;
            case ObservableEvent::CurrentlyFirst:
                score += 15;
                break;
            case ObservableEvent::CurrentlySecond:
                score += 10;
                break;
            case ObservableEvent::CurrentlyThird:
                score += 5;
                break;
            case ObservableEvent::CurrentlyForth:
                score += 2;
                break;
            case ObservableEvent::CurrentlyFifth:
                score += 1;
                break;
            case ObservableEvent::CurrentlySixth:
                score += 0;
                break;
        }

    }



    std::ostream &operator<<(std::ostream &out, const ScoreObserver& so) {
        out << so.score;
        return out;
    }

}
