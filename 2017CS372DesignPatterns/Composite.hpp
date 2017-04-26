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

class ComponentBase {
public:
    virtual ~ComponentBase()=default;
    virtual size_t size() const = 0;
    virtual void print(int tab=0) const = 0;
    virtual std::string getName() const = 0;
    virtual void accept(Visitor *v)=0;
};

template <typename T>
class Component : public ComponentBase
{
public:
    void accept(Visitor *v) override;
private:
};

class File : public Component<File>
{
    friend void print(std::shared_ptr<File> f);

public:
    File(const std::string &name, size_t size);
    size_t size() const override;
    void print(int tab=0) const override;
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

class Folder : public Component<Folder>
{
    friend     void print(std::shared_ptr<Folder> f);

public:
    Folder(std::string name);
    size_t size() const override;
    void add(std::shared_ptr<ComponentBase>);
    void print(int tab=0) const override;
    std::string getName() const override {
        return _name;
    }
    const std::vector<std::shared_ptr<ComponentBase>> & getChildren() const {
        return _elements;
    }
private:
    std::vector<std::shared_ptr<ComponentBase>> _elements;
    std::string _name;
};

#endif /* Composite_hpp */
