//
//  main.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/1/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using std::move;
#include <iostream>
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <map>
using std::map;
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <vector>
using std::vector;

#include "Expression.hpp"
// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> ( E ) | variable | number
void testInterpreter()
{
    auto five=make_unique<Number>(5);
    
    Context c;
    c["x"]=3;
    
    five->print();
    cout << endl << five->evaluate(c) << endl;
    
    auto add = make_unique<SumExpression>(num(13),num(28));
    add->print();
    cout << endl << add->evaluate(c) << endl;
    
    auto sub = make_unique<DifferenceExpression>(move(add),num(12));
    sub->print();
    cout << endl << sub->evaluate(c) << endl;
    
    auto prod = make_unique<ProductTerm>(num(4),num(5));
    prod->print();
    cout << endl << prod->evaluate(c) << endl;
    
    auto parens = make_unique<ProductTerm>(num(3),make_unique<ParenthesizedFactor>(
                                                                                   make_unique<SumExpression>(num(1),num(4))));
    parens->print();
    cout << endl << parens->evaluate(c) << endl;
    
    auto withx = make_unique<ProductTerm>(make_unique<Variable>(string("x")),make_unique<ParenthesizedFactor>(make_unique<SumExpression>(num(1),num(4))));
    
    withx->print();
    cout << endl << withx->evaluate(c) << endl;
    c["x"]=22;
    cout << endl << withx->evaluate(c) << endl;
}

#include "Monster.hpp"
void testMonster() {

    unique_ptr<Monster> tim = make_unique<Troll>("Tim");
    tim->attack();
    tim->doMovement();

    unique_ptr<Monster> bob = make_unique<Bull>("Bob");
    bob->attack();
    bob->doMovement();

    unique_ptr<Monster> mike = make_unique<Mimic>("Mike");
    mike->attack();
    mike->doMovement();
}

#include "Subject.hpp"
#include "Observer.hpp"

void testObserver() {
    Subject s;

    auto bgo =make_shared<BarGraphObserver>();
    s.attach(bgo);
    
    auto co = make_shared<CoutObserver>();
    s.attach(co);
    
    auto ao = make_shared<AlarmObserver>(13);
    s.attach(ao);
    
    auto eoo = make_shared<EvenOddObserver>();
    s.attach(eoo);
    
    s.setValue(13);
    cout << endl;
    s.setValue(5);
    cout << endl;
    s.detach(bgo);
    s.setValue(200);
}

#include "Armor.hpp"

void show(const Armor &a)
{
    cout << a.description() << " has AC " << a.getAC() << endl;
}

void testArmor()
{
    unique_ptr<Armor> pm = make_unique<PlateArmor>();
    show(*pm);

    unique_ptr<Armor> l = make_unique<LeatherArmor>();
    show(*l);
    
    unique_ptr<Armor> rpm = make_unique<RustyDecorator>(move(pm));
    show(*rpm);
    
    unique_ptr<Armor> ml = make_unique<MagicDecorator>(move(l),5);
    show(*ml);
    
    unique_ptr<Armor> mrpm = make_unique<MagicDecorator>(move(rpm),-5);
    show(*mrpm);

}

#include "Command.hpp"
void testCommand()
{
    vector<unique_ptr<Command>> buttons(10);
    for(auto &b:buttons)
        b = make_unique<NullCommand>();
    
    buttons[0] = make_unique<QuitCommand>();
    buttons[1] = make_unique<HelloCommand>();
    buttons[2] = make_unique<GoodbyeCommand>();
    
    shared_ptr<HomeObject> light = make_shared<LightObject>();
    shared_ptr<HomeObject> stereo = make_shared<StereoObject>();
    
    buttons[3] = make_unique<HomeObjectOnCommand>(light);
    buttons[4] = make_unique<HomeObjectOffCommand>(light);
    buttons[5] = make_unique<HomeObjectOnCommand>(stereo);
    buttons[6] = make_unique<HomeObjectOffCommand>(stereo);
    
    while (1) {
        cout << "Which button? " << endl;
        int b;
        cin >> b;
        if (b==-1)
            return;
        buttons[b]->execute();
    }
}

int main() {
    try {
    testCommand();
    }
    catch (...)
    {}
    return 0;
}
