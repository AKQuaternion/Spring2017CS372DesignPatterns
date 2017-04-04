//
//  Armor.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/3/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Armor_hpp
#define Armor_hpp

#include <string>
using std::string;
#include <memory>
using std::unique_ptr;
using std::move;

class Armor {
public:
    virtual ~Armor() = default;
    virtual int getAC() const = 0;
    virtual string description() const = 0;
private:
};

class PlateArmor : public Armor {
public:
    int getAC() const override  {
        return 10;
    }
    string description() const override {
        return "Plate Mail";
    }
private:
};

class LeatherArmor : public Armor {
public:
    int getAC() const override  {
        return 4;
    }
    string description() const override {
        return "Leather armor";
    }
private:
};

class ArmorDecorator : public Armor
{
public:
    ArmorDecorator(unique_ptr<Armor> component) : _component(move(component))
    {}
protected:
    string componentDescription() const{
        return _component->description();
    }
    
    int componentAC() const {
        return _component->getAC();
    }
private:
    unique_ptr<Armor> _component;
};

class RustyDecorator : public ArmorDecorator {
public:
    using ArmorDecorator::ArmorDecorator;
    
    int getAC() const override  {
        return componentAC()-2;
    }
    string description() const override {
        return "Rusty " + componentDescription();
    }
private:
};

class MagicDecorator : public ArmorDecorator {
public:
    
    MagicDecorator(unique_ptr<Armor> component, int bonus)
    : ArmorDecorator(move(component)), _bonus(bonus)
    {}
    
    int getAC() const override  {
        return componentAC()+_bonus;
    }
    string description() const override {
        return string("Magic (") + (_bonus>=0?"+":"") + std::to_string(_bonus) + ") " + componentDescription();
    }
private:
    int _bonus;
};

#endif /* Armor_hpp */
