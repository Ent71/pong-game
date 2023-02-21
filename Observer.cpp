#include "Observer.h"

#include <algorithm>

void Subject::addObserver(std::shared_ptr<Observer> observer)
{
    observers.push_back(observer);
}

void Subject::removeObserver(std::shared_ptr<Observer> observer)
{

    observers.erase(remove(observers.begin(), observers.end(), observer));
}

void Subject::notify(Subject* subject)
{
    for (std::shared_ptr<Observer> observer : observers)
    {
        observer->update(subject);
    }
}