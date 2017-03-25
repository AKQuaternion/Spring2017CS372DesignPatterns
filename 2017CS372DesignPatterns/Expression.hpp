//
//  Expression.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 3/22/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Expression_hpp
#define Expression_hpp
#include <memory>
#include <iostream>
#include <string>
#include <map>
// E -> E + T | E - T | T
// T -> T * F | T / F | F
// F -> ( E ) | variable | number

using Context = std::map<std::string,double>;

class Expression {
public:
    virtual ~Expression()=default;
    virtual double evaluate(const Context & c) const=0;
    virtual void print() const=0;
};

class Term : public Expression
{
public:
private:
};

class Factor : public Term {
};

class SumExpression : public Expression {
public:
    SumExpression(std::unique_ptr<Expression> e, std::unique_ptr<Term> t);
    double evaluate(const Context & c) const override;
    void print() const override;
    
private:
    std::unique_ptr<Expression> _e;
    std::unique_ptr<Term> _t;
};
        
class DifferenceExpression : public Expression {
public:
    DifferenceExpression(std::unique_ptr<Expression> e, std::unique_ptr<Term> t);
    double evaluate(const Context & c)const override ;
    void print()const override;
private:
    std::unique_ptr<Expression> _e;
    std::unique_ptr<Term> _t;
};

class ProductTerm : public Term {
public:
    ProductTerm(std::unique_ptr<Term> t, std::unique_ptr<Factor> f);
    double evaluate(const Context & c)const override ;
    void print()const override ;
    
private:
    std::unique_ptr<Term> _t;
    std::unique_ptr<Factor> _f;
};

class QuotientTerm : public Term {
public:
    QuotientTerm(std::unique_ptr<Term> t, std::unique_ptr<Factor> f);
    double evaluate(const Context & c) const override;
    void print() const override;
private:
    std::unique_ptr<Term> _t;
    std::unique_ptr<Factor> _f;
};


class Number : public Factor
{
public:
    Number(double n);
    double evaluate(const Context & c) const override;
    void print() const override;
    
private:
    double _n;
};

class Variable : public Factor {
public:
    Variable(const std::string &name);
    double evaluate(const Context & c) const override;
    void print() const override;
    
private:
    std::string _name;
};

class ParenthesizedFactor : public Factor {//!!! Bad class name?
public:
    ParenthesizedFactor(std::unique_ptr<Expression> e);
    double evaluate(const Context & c) const override ;
    void print() const override ;
    
private:
    std::unique_ptr<Expression> _e;
};

std::unique_ptr<Number> num(double n);

#endif /* Expression_hpp */
