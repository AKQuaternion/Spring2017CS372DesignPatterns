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

void foo()
{
    cout << "4" << endl;
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
    
    buttons[7] = make_unique<MacroCommand>(vector<shared_ptr<Command>>{make_shared<HomeObjectOnCommand>(light),
        make_shared<HomeObjectOnCommand>(stereo),
        make_shared<AnyCommand>([](){cout << "We're done!\n";}),
        make_shared<AnyCommand>(foo)
    });
    
    while (1) {
        cout << "Which button? " << endl;
        int b;
        cin >> b;
        if (b==-1)
            return;
        buttons[b]->execute();
    }
}

#include "Composite.hpp"
#include "Visitor.hpp"

void testComposite(){
    auto f1 = make_shared<File>("File1", 1);
    auto f3 = make_shared<File>("File3", 3);
    auto f5 = make_shared<File>("File5", 5);
    auto f7 = make_shared<File>("File7", 7);
    auto f9 = make_shared<File>("File9", 9);
    auto folder1 = make_shared<Folder>("Folder1");
    folder1->add(f1);
    folder1->add(f3);
    folder1->add(f5);
    folder1->add(f7);
    folder1->add(f9);
    
//    cout << f5->size() << endl;
//    cout << folder1->size() << endl;
    
    auto folder2 = make_shared<Folder>("Folder2");
    folder2->add(folder1);
    folder2->add(make_shared<File>("Big file", 1e6));
//    cout << folder2->size() << endl;
    
//    folder2->print();
    
    PrintVisitor v;
    folder2->accept(&v);
    
    SizeVisitor v2;
    folder2->accept(&v2);
    cout << v2.getSize() << endl;
}

#include "MP3Player.hpp"
void testState() {
    MP3Player m;
    m.pushSourceButton();
    m.pushNextButton();
    m.pushNextButton();
    m.pushSourceButton();
    m.pushNextButton();
    m.pushNextButton();
    m.pushSourceButton();
    m.pushNextButton();
    m.pushNextButton();
}

int main() {
    try {
    testComposite();
    }
    catch (...)
    {}
    return 0;
}
