#pragma once
#include "inputevent.h"
#include "../vector.h"


// Mouse click specific data
class MouseButtonData : public InputEvent::Data {
public:
	Geom::Vector coords;
	//bool state; //false - for released, true - for pressed
	/*enum MouseButton {
		LEFT_BUTTON = 1, MIDDLE_BUTTON = 2, RIGHT_BUTTON = 3
	} button;*/
	std::string button;

	MouseButtonData(const std::string&, const Geom::Vector& v = Geom::Vector(0, 0));
	virtual bool operator<(const Data*) const;
	virtual Data* clone() const;
	virtual ~MouseButtonData() {}
};