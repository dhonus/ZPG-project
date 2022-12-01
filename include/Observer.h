//
// Created by daniel on 12.10.22.
//

#ifndef ZPG_OBSERVER_H
#define ZPG_OBSERVER_H

#include <vector>
#include <algorithm>
#include <iostream>

class Subject;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(Subject&) = 0;
};

class Subject{
private:
    std::vector<Observer*> observers;
public:
    virtual ~Subject() = default;
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notify();
};

#endif //ZPG_OBSERVER_H
