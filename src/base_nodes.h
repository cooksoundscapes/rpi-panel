#include <map>
#include <string>
#include <functional>
#include "cairo_context.h"

class DisplayNode {    
public:
    const Pencil& screen; 

    Node(const Pencil& ctx) : screen{ctx} {}

    virtual void render() {}
};

class ControlNode {
public:
    virtual void onKnob(int state) {}
};

class TextParameter : public ControlNode, public DisplayNode {
public: 

    double value{0}, min, max;
    std::string address, unit, label;

    TextParameter
    (const Pencil& screen, std::string address, std::string unit, std::string label, double min, double max)
    : DisplayNode(screen)
    {
        this->address = address;
        this->unit = unit;
        this->label = label;
        this->min = min;
        this->max = max;
    }

    void onKnob(int state) {
        value = std::min(max, std::max(min, state+value));
    }

    void render() {
        screen.drawText(label + ": " + std::to_string(value) + unit);
    }
};