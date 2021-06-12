#pragma once
#include <string>


enum class InputEventType {
	UNKNOWN, MOUSE_BUTTON, MOUSE_MOTION, MOUSE_WHEEL_SCROLL, KEYBOARD, QUIT
};

//InputEventType String_to_InputEventType(const std::string&);
//std::string InputEventType_to_String(const InputEventType&);


class InputEvent {
public:
	InputEvent();
	InputEvent(const InputEvent&);
	~InputEvent();

	InputEventType type;
	// indicates pressed or released button is, true if axis
	bool state;
	// Data class of the event, inheritors provide specific info, depending on type of event
	class Data {
	public:
		virtual bool operator<(const Data*) const = 0;
		virtual Data* clone() const = 0;
		virtual ~Data() {};
	} *data;

	bool operator<(const InputEvent& b) const;

	// Comparators are used in std::map to compare events without time- and place-specific info
	class Comp {
	public:
		bool operator()(const InputEvent& a, const InputEvent& b) const {
			return a < b;
		}
	};
};
