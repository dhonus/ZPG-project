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
    void attach(Observer *observer) {
        observers.push_back(observer);
    }
    void detach(Observer *observer){
        observers.erase(std::remove(observers.begin(), observers.end(), observer));
    }
    void notify(){
        for (auto& o : observers){
            o->update(*this);
        }
    }
};

#endif //ZPG_OBSERVER_H
