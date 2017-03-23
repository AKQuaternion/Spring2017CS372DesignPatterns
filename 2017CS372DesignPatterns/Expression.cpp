//
//  Expression.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/22/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//
// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> ( E ) | variable | number

#include "Expression.hpp"

SumExpression::SumExpression(std::unique_ptr<Expression> e, std::unique_ptr<Term> t) :
_e(move(e)), _t(move(t))
{}

double SumExpression::evaluate(const Context & c) const  {
    return _e->evaluate(c) + _t->evaluate(c);
}
void SumExpression::print()const  {
    _e->print(); std::cout << " + "; _t->print();
}

DifferenceExpression::DifferenceExpression(std::unique_ptr<Expression> e, std::unique_ptr<Term> t) :
_e(move(e)), _t(move(t))
{}

double DifferenceExpression::evaluate(const Context & c)const  {
    return _e->evaluate(c) - _t->evaluate(c);
}
void DifferenceExpression::print()const{
    _e->print(); std::cout << " - "; _t->print();
}

ProductTerm::ProductTerm(std::unique_ptr<Term> t, std::unique_ptr<Factor> f) :
_t(move(t)), _f(move(f))
{}

double ProductTerm::evaluate(const Context & c)const  {
            return _t->evaluate(c) * _f->evaluate(c);
        }

void ProductTerm::print()const  {
            _t->print(); std::cout << " * "; _f->print();
        }

QuotientTerm::QuotientTerm(std::unique_ptr<Term> t, std::unique_ptr<Factor> f) :
    _t(move(t)), _f(move(f))
    {}

double QuotientTerm::evaluate(const Context & c) const  {
    return _t->evaluate(c) / _f->evaluate(c);
}

void QuotientTerm::print() const  {
    _t->print(); std::cout << " / "; _f->print();
}
    
Number::Number(double n):_n(n) {
}

double Number::evaluate(const Context & c) const  {
    return _n;
}

void Number::print() const  {
    std::cout << _n;
}

Variable::Variable(const std::string &name):_name(name)
{}

double Variable::evaluate(const Context & c) const  {
    return c.find(_name)->second; //!!!unsafe
}

void Variable::print() const {
    std::cout << _name;
}

ParenthesizedFactor::ParenthesizedFactor(std::unique_ptr<Expression> e):_e(move(e))
{}

double ParenthesizedFactor::evaluate(const Context & c) const  {
    return _e->evaluate(c);
}

void ParenthesizedFactor::print() const  {
    std::cout << "( "; _e->print(); std::cout << " )";
}
    
std::unique_ptr<Number> num(double n)
{
    return std::make_unique<Number>(n);
}
