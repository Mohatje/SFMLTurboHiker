#include "Observable.h"

namespace turbohiker {

void Observable::addObserver(Observable::SharedObserverRef observer) { observerVector.push_back(observer); }

void Observable::notifyObservers(ObservableEvent event)
{
        for (auto& observer : observerVector)
                observer->onNotify(event);
}
} // namespace turbohiker
