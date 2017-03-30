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


int main() {
    testObserver();
    return 0;
}
