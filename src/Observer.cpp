//
// Created by daniel on 12.10.22.
//

#include "../include/Observer.h"

void Subject::attach(Observer *observer) {
    observers.push_back(observer);
}

void Subject::detach(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer));
}

void Subject::notify() {
    for (auto& o : observers){
        o->update(*this);
    }
}
