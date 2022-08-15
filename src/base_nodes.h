#pragma once
#include <map>
#include <string>
#include <functional>
#include <vector>
#include "cairo_context.h"

class Node {
public:
    virtual ~Node() {}
    virtual void render(const Pencil& screen) {};
    virtual void onKnob(int state) {};
};

class TextParameter : public Node {
public: 

    double value{0}, min, max;
    std::string address, unit, label;

    TextParameter() = default;

    TextParameter(
        const std::string& address, 
        const std::string& unit, 
        const std::string& label, 
        double min, 
        double max,
        double value = 0)
    {
        this->address = address;
        this->unit = unit;
        this->label = label;
        this->min = min;
        this->max = max;
        this->value = value;
    }

    void onKnob(int state) {
        value = std::min(max, std::max(min, state+value));
    }

    void render(const Pencil& screen) {
        screen.drawText(label + ": " + std::to_string(value) + unit);
    }
};

class Tabs : public Node {
public:
    int tabs, selected{0};
 
    Tabs() = default;

    Tabs(int amount) : tabs{amount} {}

    void onKnob(int state) {
        tabs = std::max(0, std::min(tabs, selected + state));
    }
};

//--------------------Factory----------------------

std::map<std::string, std::function<Node*()>> const factories = {
    { "Tabs", [](){ return new Tabs(); } },
    { "TextParameter", [](){ return new TextParameter(); } },
};

class NodeFactory {
public:
    static Node* createNode(const std::string& type) {
        return factories.at(type)();
    }
};
