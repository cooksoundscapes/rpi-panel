#include "i2c_device.h"
#include <bitset>
#include <functional>
#include <array>

class PCF8574: public DeviceI2C {
public:
	using State = std::bitset<8>;

	template<int I>
	using Actions = std::array<std::function<void(int)>, I>;

	PCF8574(int addr): DeviceI2C(addr) {}

	~PCF8574() {}

	void read() const {
		auto response = i2c_smbus_read_byte_data(file, 0xff);
		if (response < 0) {
			std::cout << "Error reading device" << '\n';
			return;
		}
		auto newState = std::bitset<8>(response);
		triggerActions(newState);
		state = newState;
	}

	virtual void triggerActions(State) {}
	virtual void setAction(int control, std::function<void(int)> action) {}

protected:
	State state;
	__s32 lastRead;
};

class ButtonArray : public PCF8574 {
public:
	ButtonArray(int addr) : PCF8574{addr} {}

	void setAction(int button, std::function<void(int)> action) {
		if (button < 1 || button > 8) {
			std::cout << "Button number outside range;\n";
			return;
		}
		actions[button-1] = action;
	}

	void triggerActions(State newState) {
		for (int i{0}; i < 8; i++) {
			if (state[i] != newState[i]) {
				if (actions[i] != nullptr) 
					actions[i](state[i]); // call the assigned lambda with button state as argument!
			}
		}
	}
protected:
	Actions<8> actions;
};



class EncoderArray : public PCF8574 {
public: 
	EncoderArray(int addr) : PCF8574{addr} {}

	void setAction(int encoder, std::function<void(int)> action) {
		if (encoder < 1 || encoder > 4) {
			std::cout << "Encoder number outside range;'\n";
			return;
		}
		actions[encoder-1] = action;
	}

protected:
	Actions<4> actions;
};