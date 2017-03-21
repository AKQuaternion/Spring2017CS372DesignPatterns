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

// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> ( E ) | variable | number

using Context = map<string,double>;

class Expr {
public:
    virtual ~Expr()=default;
    virtual double evaluate(const Context & c)const=0;
    virtual void print()const=0;
};

class Term : public Expr
{
public:
private:
    
};

class Factor : public Term {
    
};

class SumExpr : public Expr {
public:
    SumExpr(unique_ptr<Expr> e, unique_ptr<Term> t) :
      _e(move(e)), _t(move(t))
    {}
    double evaluate(const Context & c)const override {
        return _e->evaluate(c) + _t->evaluate(c);
    }
    void print()const override {
        _e->print(); cout << " + "; _t->print();
    }
    
private:
    unique_ptr<Expr> _e;
    unique_ptr<Term> _t;
};

class DifferenceExpr : public Expr {
public:
    DifferenceExpr(unique_ptr<Expr> e, unique_ptr<Term> t) :
    _e(move(e)), _t(move(t))
    {}
    double evaluate(const Context & c)const override {
        return _e->evaluate(c) - _t->evaluate(c);
    }
    void print()const override {
        _e->print(); cout << " - "; _t->print();
    }
    
private:
    unique_ptr<Expr> _e;
    unique_ptr<Term> _t;
};

class ProductTerm : public Term {
public:
    ProductTerm(unique_ptr<Term> t, unique_ptr<Factor> f) :
    _t(move(t)), _f(move(f))
    {}
    double evaluate(const Context & c)const override {
        return _t->evaluate(c) * _f->evaluate(c);
    }
    void print()const override {
        _t->print(); cout << " * "; _f->print();
    }
    
private:
    unique_ptr<Term> _t;
    unique_ptr<Factor> _f;
};

class QuotientTerm : public Term {
public:
    QuotientTerm(unique_ptr<Term> t, unique_ptr<Factor> f) :
    _t(move(t)), _f(move(f))
    {}
    double evaluate(const Context & c) const override {
        return _t->evaluate(c) / _f->evaluate(c);
    }
    void print() const override {
        _t->print(); cout << " / "; _f->print();
    }
    
private:
    unique_ptr<Term> _t;
    unique_ptr<Factor> _f;
};


class Number : public Factor
{
public:
    Number(double n):_n(n) {
    }
    double evaluate(const Context & c) const override {
        return _n;
    }
    void print() const override {
        cout << _n;
    }

private:
    double _n;
};

class Variable : public Factor {
public:
    Variable(const string &name):_name(name)
    {}
    double evaluate(const Context & c) const override {
        return c.find(_name)->second; //!!!unsafe
    }
    void print() const override {
        cout << _name;
    }
    
private:
    string _name;
};
        
class ParenthesizedFactor : public Factor {//!!! Bad class name?
public:
    ParenthesizedFactor(unique_ptr<Expr> e):_e(move(e))
    {}
    double evaluate(const Context & c) const override {
        return _e->evaluate(c);
    }
    void print() const override {
        cout << "( "; _e->print(); cout << " )";
    }
    
private:
    unique_ptr<Expr> _e;
};

unique_ptr<Number> num(double n)
{
    return make_unique<Number>(n);
}

#include <iostream>
using std::cout;
using std::endl;

int main() {
    auto five=make_unique<Number>(5);
    
    Context c;
    c["x"]=3;
    
    five->print();
    cout << endl << five->evaluate(c) << endl;
    
    auto add = make_unique<SumExpr>(num(13),num(28));
    add->print();
    cout << endl << add->evaluate(c) << endl;
    
    auto sub = make_unique<DifferenceExpr>(move(add),num(12));
    sub->print();
    cout << endl << sub->evaluate(c) << endl;

    auto prod = make_unique<ProductTerm>(num(4),num(5));
    prod->print();
    cout << endl << prod->evaluate(c) << endl;
    
    auto parens = make_unique<ProductTerm>(num(3),make_unique<ParenthesizedFactor>(
                                make_unique<SumExpr>(num(1),num(4))));
    parens->print();
    cout << endl << parens->evaluate(c) << endl;

    auto withx = make_unique<ProductTerm>(make_unique<Variable>(string("x")),make_unique<ParenthesizedFactor>(make_unique<SumExpr>(num(1),num(4))));

    withx->print();
    cout << endl << withx->evaluate(c) << endl;
    c["x"]=22;
    cout << endl << withx->evaluate(c) << endl;
    return 0;
}
