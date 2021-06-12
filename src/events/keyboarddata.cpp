#include "keyboarddata.h"

KeyboardData::KeyboardData(sf::Keyboard::Key key, int m) : key(key), modifiers(m) {}

bool KeyboardData::operator<(const Data* d) const {
	const KeyboardData* kd = static_cast<const KeyboardData*>(d);
	/*if (state != kd->state)
		return state < kd->state;*/
	if (key != kd->key)
		return key < kd->key;
	return modifiers < kd->modifiers;
}

InputEvent::Data* KeyboardData::clone() const {
	KeyboardData* res = new KeyboardData(*this);
	return res;
}