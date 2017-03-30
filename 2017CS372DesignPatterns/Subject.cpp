//
//  Subject.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/29/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include "Subject.hpp"
#include "Observer.hpp"
#include <algorithm>

void Subject::attach(std::shared_ptr<Observer> oPtr){
    _observers.push_back(oPtr);
}

void Subject::detach(std::shared_ptr<Observer> oPtr){
    auto i = std::find(_observers.begin(), _observers.end(), oPtr);
    _observers.erase(i);
}

void Subject::setValue(int n){
    _value = n;
    notify();
}

int Subject::getValue() const{
    return _value;
}


void Subject::notify() const{
    for(auto oPtr:_observers)
        oPtr->update(_value);
}


