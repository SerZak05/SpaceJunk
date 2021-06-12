#pragma once
#include "inputevent.h"


class KeyboardData : public InputEvent::Data {
public:
	char key;
	//bool state;
	enum KeyMod {
		SHIFT = 1, CTRL = 2, ALT = 4, CAPS_LOCK = 8
	};
	int modifiers;

	KeyboardData(char key, int modifiers = 0);
	virtual bool operator<(const Data*) const;
	virtual Data* clone() const;
	virtual ~KeyboardData() {}
};