//
//  Monster.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/24/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Monster_hpp
#define Monster_hpp

#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
using std::move;
#include <memory>
using std::unique_ptr;
using std::make_unique;

class MovementPolicy {
public:
    virtual ~MovementPolicy()=default;
    virtual void doMovement() const =0;
private:
};

class WalkMovement : public MovementPolicy {
public:
    void doMovement() const override {
        cout << " walks." << endl;
        }
        };
        
    class NoMovement : public MovementPolicy {
    public:
        void doMovement() const override {
            cout << " sits there." << endl;
        }
    };
        
class Monster {
public:
    Monster(string name, unique_ptr<MovementPolicy> movePolicyPtr)
       :_name(move(name)),_movePolicyPtr(move(movePolicyPtr))
    {}
    virtual void attack() const =0;
    virtual void doMovement() const {
        cout << _name;
        _movePolicyPtr->doMovement();
    }
    virtual ~Monster() = default;
protected:
    const string _name;
    unique_ptr<MovementPolicy> _movePolicyPtr;
    
};

class Troll : public Monster {
    using Monster::Monster;
public:
    Troll(string name):Monster(move(name),make_unique<WalkMovement>()) {
    }
    void attack() const override {
        cout << _name << " swings it's mace." << endl;
    }
        
};

class Bull : public Monster {
    using Monster::Monster;
public:
    Bull(string name):Monster(move(name),make_unique<WalkMovement>()) {
    }
    void attack() const override {
        cout << _name << " gores." << endl;
    }
    
};

class Mimic : public Monster {
    using Monster::Monster;
public:
    Mimic(string name):Monster(move(name),make_unique<NoMovement>()) {
    }
    void attack() const override {
        cout << _name << " bites." << endl;
    }
    
};

#endif /* Monster_hpp */
