//
//  Visitor.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/12/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include "Visitor.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;

void PrintVisitor::visit(const File *f) {
    cout << setw(_tab) << " " << f->getName() << endl;
}

void PrintVisitor::visit(const Folder *f) {
    cout << setw(_tab) << " " << f->getName() << endl;
    _tab += 4;
    for (auto c:f->getChildren())
        c->accept(this);
    _tab -= 4;
}

void SizeVisitor::visit(const File *f) {
    _size += f->getSize();
}

void SizeVisitor::visit(const Folder *f) {
    for (auto c:f->getChildren())
        c->accept(this);
}
