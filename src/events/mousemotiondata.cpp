#include "mousemotiondata.h"

MouseMotionData::MouseMotionData(const Geom::Vector& screenCoords) :
	screenCoords(screenCoords) {}

bool MouseMotionData::operator<(const Data*) const {
	return false;
}

InputEvent::Data* MouseMotionData::clone() const {
	return new MouseMotionData(screenCoords);
}
