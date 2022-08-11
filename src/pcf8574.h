#include "i2c_device.h"
#include <bitset>
#include <functional>
#include <array>

class PCF8574: public DeviceI2C {
private:
	std::bitset<8> state;
	__s32 lastRead;
	std::array<std::function<void(int)>, 8> actions;

public:
	PCF8574(int addr): DeviceI2C(addr) {}

	~PCF8574() {}

	void setAction(int button, std::function<void(int)> action) {
		if (button < 1 || button > 8) {
			std::cout << "Button number outside range;\n";
			return;
		}
		actions[button-1] = action;
	}

	void read() {
		auto response = i2c_smbus_read_byte_data(file, 0xff);
		if (response < 0) {
			std::cout << "Error reading device" << '\n';
			return;
		}
		auto newState = std::bitset<8>(response);
		for (int i{0}; i < 8; i++) {
			if (state[i] != newState[i]) {
				if (actions[i] != nullptr) 
					actions[i](state[i]); // call the assigned lambda with button state as argument!
			}
		}
		state = newState;
	}
};
