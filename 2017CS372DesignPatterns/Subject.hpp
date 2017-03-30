//
//  Subject.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/29/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Subject_hpp
#define Subject_hpp

#include <vector>
#include <memory>

class Observer;

class Subject {
public:
    void attach(std::shared_ptr<Observer>);
    void detach(std::shared_ptr<Observer>);
    void setValue(int n);
    int getValue() const;
    void notify() const;
private:
    std::vector<std::shared_ptr<Observer>> _observers;
    int _value;
};

#endif /* Subject_hpp */
