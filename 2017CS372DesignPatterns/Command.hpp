//
//  Command.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/5/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp
#include <iostream>
using std::cout;
using std::endl;
#include <memory>
using std::shared_ptr;

class Command {
public:
    virtual ~Command()=default;
    virtual void execute() const = 0;
private:
};

class NullCommand : public Command
{
public:
    void execute() const override {
        }
};

class HelloCommand : public Command
{
public:
    void execute() const override {
        cout << "Hello!" << endl;
    }
};
        
class GoodbyeCommand : public Command
{
public:
    void execute() const override {
        cout << "Goodbye!" << endl;
    }
};

class QuitCommand : public Command
{
public:
    void execute() const override {
        throw 0;
    }
};
        
class HomeObject {
public:
    virtual ~HomeObject() = default;
    virtual void on()=0;
    virtual void off()=0;
private:
};

class LightObject : public HomeObject {
public:
    void on() override {
        cout << "light is on" << endl;
    }
    void off() override {
        cout << "light is off" << endl;
    }
private:
};

class StereoObject : public HomeObject {
public:
    void on() override {
        cout << "stereo is on" << endl;
    }
    void off() override {
        cout << "stereo is off" << endl;
    }
private:
};
        
class HomeObjectOnCommand : public Command {
public:
    HomeObjectOnCommand(shared_ptr<HomeObject> receiver) : _receiver(receiver)
    {}
    void execute() const override {
        _receiver->on();
    }
private:
    shared_ptr<HomeObject> _receiver;
};
        
class HomeObjectOffCommand : public Command {
public:
    HomeObjectOffCommand(shared_ptr<HomeObject> receiver) : _receiver(receiver)
    {}
    void execute() const override {
        _receiver->off();
    }
private:
    shared_ptr<HomeObject> _receiver;
};
        
class Door {
public:
    void open() {
        cout << "Door is open." << endl;
    }
    void close() {
        cout << "Door is closed." << endl;
    }
private:
};

class DoorHomeObject : public HomeObject
{
public:
    void on() override
    {
        _d.open();
    }
    void off() override {
        _d.close();
    }
private:
    Door _d;
};
#endif /* Command_hpp */
