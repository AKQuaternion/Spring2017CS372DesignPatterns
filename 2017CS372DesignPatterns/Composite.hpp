//
//  Composite.hpp
//  2017CS372DesignPatterns
//
//  Created by Chris Hartman on 4/12/17.
//  Copyright © 2017 Chris Hartman. All rights reserved.
//

#ifndef Composite_hpp
#define Composite_hpp

#include <cstddef>
#include <vector>
#include <memory>
#include <string>

class Visitor;

class Component
{
public:
    virtual ~Component() = default;
    virtual size_t size() const = 0;
    virtual void print(int tab=0) const = 0;
    virtual void accept(Visitor *v) const = 0;
    virtual std::string getName() const = 0;
private:
};

class File : public Component
{
    friend void print(std::shared_ptr<File> f);

public:
    File(const std::string &name, size_t size);
    size_t size() const override;
    void print(int tab=0) const override;
    void accept(Visitor *v) const override;
    std::string getName() const override {
        return _name;
    }
    size_t getSize() const  {
        return _size;
    }
protected:
    
private:
    size_t _size;
    std::string _name;
};

class Folder : public Component
{
    friend     void print(std::shared_ptr<Folder> f);

public:
    Folder(std::string name);
    size_t size() const override;
    void add(std::shared_ptr<Component>);
    void print(int tab=0) const override;
    void accept(Visitor *v) const override;
    std::string getName() const override {
        return _name;
    }
    const std::vector<std::shared_ptr<Component>> & getChildren() const {
        return _elements;
    }
private:
    std::vector<std::shared_ptr<Component>> _elements;
    std::string _name;
};

#endif /* Composite_hpp */
