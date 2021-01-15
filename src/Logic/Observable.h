#pragma once
#include "Observer.h"
#include <vector>
#include <memory>

namespace turbohiker {
    class Observable {
    public:
        using SharedObserverRef = std::shared_ptr<Observer>;
    public:
        /**
         * Method to add an Observer to the List of observers of an Observable Entity
         * @param observer shared pointer to an observer
         */
        void addObserver(SharedObserverRef observer);

        /**
         * Method to notify all observers of an event
         * @param event Some observable event
         */
        virtual void notifyObservers(ObservableEvent event);

    private:
        std::vector<SharedObserverRef> observerVector;
    };
}