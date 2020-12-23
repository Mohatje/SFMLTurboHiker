#pragma once
#include "Observer.h"
#include <vector>
#include <memory>

namespace turbohiker {
    class Observable {
    public:
        using SharedObserverRef = std::shared_ptr<Observer>;
    public:
        void addObserver(SharedObserverRef observer);

        virtual void notifyObservers(ObservableEvent event);

    private:
        std::vector<SharedObserverRef> observerVector;
    };
}