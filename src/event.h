#pragma once

enum EventType {
	SCENE_EVENT,
	EXIT_EVENT,
	EVENT_TYPE_TOTAL
};

/*enum InputEventType {
	KEYBOARD, MOUSE, TOUCH
};*/
class Event {
public:
	Event(EventType t);
	virtual ~Event();

	EventType type;
};

// key
/*class EventSpec {
	InputEventType type;
	
};
class InputEvent {
	isPressed() {
		return _state == SDL_PRESSED
	}
};
class KeyboardEvent : InputEvent {
	//const static int TYPE_ID = "KeyboardEvent"
	// modifiers
	std::vector<bool> modifiers;
	// shift, ctrl, alt, meta, 
	int keyCode;
};

class MouseEvent : InputEvent {
	//const static int TYPE_ID = "MouseEvent"
};
*/
