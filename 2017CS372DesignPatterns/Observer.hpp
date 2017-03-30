//
//  Observer.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/29/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Observer_hpp
#define Observer_hpp

class Observer {
public:
    virtual ~Observer()=default;
    virtual void update(int) const=0;
private:
};

class BarGraphObserver : public Observer {
public:
    void update(int n) const override;
};

class CoutObserver : public Observer {
public:
    void update(int n) const override;
};

class AlarmObserver : public Observer {
public:
    void update(int n) const override;
    AlarmObserver(int alarm=10);
private:
    int _alarmValue;
};

class EvenOddObserver : public Observer {
public:
    void update(int n) const override;
};


#endif /* Observer_hpp */
