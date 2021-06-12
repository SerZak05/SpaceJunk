#include "mousebuttondata.h"

MouseButtonData::MouseButtonData(const std::string& b, const Geom::Vector& v)
	: coords(v), button(b)
{
	/*if (state)
		type = InputEventType::MOUSE_BUTTON_DOWN;
	else
		type = InputEventType::MOUSE_BUTTON_UP;*/
}

bool MouseButtonData::operator<(const Data* d) const {
	const MouseButtonData* md = static_cast<const MouseButtonData*>(d);
	/*if (state != md->state)
		return state < md->state;*/
	return button < md->button;
}

InputEvent::Data* MouseButtonData::clone() const {
	Data* res = new MouseButtonData(button, coords);
	return res;
}