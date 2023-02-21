#pragma once

#include <vector>
#include <memory>

class Observer;

class Subject
{
public:
    void addObserver(std::shared_ptr<Observer> observer);
    void removeObserver(std::shared_ptr<Observer> observer);
    virtual void notify(Subject* subject);

protected:
    std::vector<std::shared_ptr<Observer>> observers;
};

class Observer
{
public:
    virtual void update(Subject* subject) = 0;
};
