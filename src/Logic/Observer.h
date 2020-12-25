#pragma once

#include <ostream>
#include <memory>

namespace turbohiker {

    class Entity;

    enum class ObservableEvent {
        None = 0,
        FinishedFirst = 1,
        FinishedSecond = 2,
        FinishedThird = 3,
        FinishedForth = 4,
        FinishedFifth = 5,
        FinishedSixth = 6,

        Collision = 7,
        Yelled = 8,

        WorldSpeed = 9,
        CurrentlyFirst = 10,
        CurrentlySecond = 11,
        CurrentlyThird = 12,
        CurrentlyForth = 13,
        CurrentlyFifth = 14,
        CurrentlySixth = 15
    };

    class Observer {
    public:
        Observer() = default;
        virtual ~Observer() = default;

        virtual void onNotify(ObservableEvent event) = 0;

    };

}

