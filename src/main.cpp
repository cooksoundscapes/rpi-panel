#include "main.h"

int main(int argc, char** argv) 
{
	PCF8574 buttons{0x21};
	Pencil cairo{128, 64};
	SSD1306 display(0x3c);
	XmlParser xml;

	Panel panel{cairo, xml, display, buttons};

	panel.loop();

	return 0;
}
