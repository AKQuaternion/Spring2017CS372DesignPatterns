//
//  Visitor.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/12/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Visitor_hpp
#define Visitor_hpp

#include "Composite.hpp"

class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(const File *) = 0;
    virtual void visit(const Folder *) = 0;
};

class PrintVisitor : public Visitor {
public:
    virtual void visit(const File *);
    virtual void visit(const Folder *);
private:
    int _tab=0;
};

class SizeVisitor : public Visitor {
public:
    virtual void visit(const File *);
    virtual void visit(const Folder *);
    size_t getSize() const {return _size;}
private:
    size_t _size=0;
};
#endif /* Visitor_hpp */
