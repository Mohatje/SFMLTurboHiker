#pragma once

#include <ostream>
#include <memory>

namespace turbohiker {

    class Entity;

    enum class ObservableEvent {
        None = 0,
        Collision = 1,
        FinishedFirst = 2,
        FinishedSecond = 3,
        FinishedThird = 4,
        FinishedForth = 5,
        FinishedFifth = 6,
        FinishedSixth = 7,
        Yelled = 8
    };

    class Observer {
    public:
        Observer() = default;
        virtual ~Observer() = default;

        virtual void onNotify(ObservableEvent event) = 0;

        virtual std::ostream &operator<<(std::ostream &os) const = 0;


    };

}

