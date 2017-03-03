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

// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> ( E ) | number

class Expr{
public:
    virtual ~Expr()=default;
    virtual double evaluate()=0;
};

class Term : public Expr
{
public:
private:
    
};

class SumExpr : public Expr {
public:
    SumExpr(unique_ptr<Expr> e, unique_ptr<Term> t) :
      _e(move(e)), _t(move(t))
    {}
    double evaluate() override {
        return _e->evaluate() + _t->evaluate();
    }
    
private:
    unique_ptr<Expr> _e;
    unique_ptr<Term> _t;
};

class Factor : public Term {
    
};

class Number : public Factor
{
public:
    Number(double n):_n(n) {
    }
    double evaluate() override {
        return _n;
    }
private:
    double _n;
};


#include <iostream>
using std::cout;
using std::endl;

int main() {
    auto five=make_unique<Number>(5);
    
    cout << five->evaluate() << endl;
    
    auto add = make_unique<SumExpr>(make_unique<Number>(13),make_unique<Number>(28));
    cout << add->evaluate() << endl;
    
    return 0;
}
