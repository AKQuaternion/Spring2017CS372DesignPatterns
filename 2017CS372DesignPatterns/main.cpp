//
//  main.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/1/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include <memory>
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


int main() {
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
    return 0;
}
