#include <unistd.h>
#include "cairo_context.h"
#include "pcf8574.h"
#include "ssd1306.h"
#include <signal.h>

SSD1306 display(0x3c);

void cancelHandler(int s) {
	display.clear();
	exit(0);
}

int main(int argc, char** argv) 
{
	PCF8574 buttons{0x21};

	Pencil cairo{128, 64};

	signal(SIGINT, cancelHandler);

	cairo.beginDrawing();

	cairo.helloho();

	buttons.setAction(1, [=](int state){
		if (state == 1) display.stripes();
	});

	display.drawBuffer(cairo.endDrawing());

	while (true) {
		buttons.read();
	
		usleep(10000);
	}

	return 0;
}
