#include "inputevent.h"


/*InputEventType String_to_InputEventType(const std::string& str) {
	if (str == "MOUSE_BUTTON_DOWN")
		return InputEventType::MOUSE_BUTTON_DOWN;
	if (str == "MOUSE_BUTTON_UP")
		return InputEventType::MOUSE_BUTTON_UP;
	if (str == "MOUSE_MOVE")
		return InputEventType::MOUSE_MOVE;
	if (str == "MOUSE_SCROLL")
		return InputEventType::MOUSE_SCROLL;
	if (str == "KEYBOARD_DOWN")
		return InputEventType::KEYBOARD_DOWN;
	if (str == "KEYBOARD_UP")
		return InputEventType::KEYBOARD_UP;
	if (str == "QUIT")
		return InputEventType::QUIT;
	return InputEventType::UNKNOWN;
}

std::string InputEventType_to_String(const InputEventType& t) {
	switch (t) {
	case InputEventType::MOUSE_BUTTON_DOWN:
		return "MOUSE_BUTTON_DOWN";
	case InputEventType::MOUSE_BUTTON_UP:
		return "MOUSE_BUTTON_UP";
	case InputEventType::MOUSE_MOVE:
		return "MOUSE_MOVE";
	case InputEventType::MOUSE_SCROLL:
		return "MOUSE_SCROLL";
	case InputEventType::KEYBOARD_DOWN:
		return "KEYBOARD_DOWN";
	case InputEventType::KEYBOARD_UP:
		return "KEYBOARD_UP";
	case InputEventType::QUIT:
		return "QUIT";
	default:
		return "UNKNOWN";
	}
}
*/

InputEvent::InputEvent() : type(InputEventType::UNKNOWN), data(nullptr) {}
InputEvent::InputEvent(const InputEvent& inp_ev) : type(inp_ev.type), state(inp_ev.state) {
	if (inp_ev.data == nullptr)
		data = nullptr;
	else
		data = inp_ev.data->clone();
}

InputEvent::~InputEvent() {
	delete data;
}

bool InputEvent::operator<(const InputEvent& b) const {
	if (type != b.type) {
		return type < b.type;
	}
	else if (state != b.state) {
		return state < b.state;
	}
	return data->operator<(b.data);
}
