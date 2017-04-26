//
//  Composite.cpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/12/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#include "Composite.hpp"
#include "Visitor.hpp"
using std::string;
#include <iostream>
using std::cout;
using std::endl;
#include <iomanip>
using std::setw;
#include <memory>
using std::shared_ptr;

template <typename T>
void Component<T>::accept(Visitor *v)
{
    v->visit(static_cast<T*>(this));
}

File::File(const string &name, size_t size) :_name(name), _size(size)
{}

size_t File::size() const {
    return _size;
}

void File::print(int tab) const {
    std::cout << setw(tab) << " " << _name << endl;
}

size_t Folder::size() const {
    size_t total=0;
    for(auto i:_elements)
        total += i->size();
    return total;
}

Folder::Folder(std::string name):_name(name)
{}

void Folder::add(std::shared_ptr<ComponentBase> f) {
    _elements.push_back(f);
}

void Folder::print(int tab) const {
    cout << setw(tab) << " " << _name << endl;
    for(auto i:_elements)
        i->print(tab+4);
}
