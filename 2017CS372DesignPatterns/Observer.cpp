//
//  Observer.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/29/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include "Observer.hpp"
#include <iostream>
using std::cout;
using std::endl;

void BarGraphObserver::update(int n) const {
    for(int ii=0;ii<n;++ii)
        cout << "*";
    cout << endl;
}

void CoutObserver::update(int n) const {
    cout << n << endl;
}

//default alarm=10
AlarmObserver::AlarmObserver(int alarm):_alarmValue(alarm)
{}

void AlarmObserver::update(int n) const {
    if (n>_alarmValue)
        cout << "Alarm!!!" << endl;
}

void EvenOddObserver::update(int n) const {
    if (n%2==0)
        cout << "Even." << endl;
    else
        cout << "Odd." << endl;
}
