#pragma once

#include <memory>
#include <ostream>

namespace turbohiker {

class Entity;

enum class ObservableEvent
{
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

class Observer
{
public:
        /**
         * Default constructor
         */
        Observer() = default;
        /**
         * Default destructor
         */
        virtual ~Observer() = default;

        /**
         * Method to receive notifications and handle incoming events
         * @param event an ObservableEvent which needs to be handled
         */
        virtual void onNotify(ObservableEvent event) = 0;

        /**
         * Generic interface method to get a value from an observer
         * @return value of observer
         */
        virtual int getValue() = 0;
};

} // namespace turbohiker
