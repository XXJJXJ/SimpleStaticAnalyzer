#pragma once
#include <string>

using namespace std;

class Entity {
public:
    ~Entity() {};
};

class Statement : public Entity {};

class Procedure : public Entity {};

class Constant : public Entity {
protected:
    int value;
public:
    Constant(int val) : value(val) {};
    int getValue() const { return value; }
};

class Variable : public Entity {
protected:
    string name;
public:
    Variable(string var) : name(var) {};
    string getName() const { return name; }
};