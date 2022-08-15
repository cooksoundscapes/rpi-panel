#include "cairo_context.h"
#include "xml_parser.h"
#include "ssd1306.h"
#include "pcf8574.h"
#include "base_nodes.h"
#include <unistd.h>

Node* createNode(std::string);

class Panel 
{
    const Pencil& screen;
    const XmlParser& xmlParser;
    const SSD1306 display; 
    const PCF8574 buttonConsole;

public:
    Panel() = default;
    Panel(
        const Pencil& scr, 
        const XmlParser& xml, 
        const SSD1306& disp, 
        const PCF8574& btns
    ) : screen{scr}, xmlParser{xml}, display{disp}, buttonConsole{btns} {}

    ~Panel() {
        display.clear();
    }

    void loop() {
        while(1) {
            buttonConsole.read();
            usleep(10000);
        }
    }
}; 