#include "mousemotiondata.h"

MouseMotionData::MouseMotionData(const Geom::Vector& screenCoords, const Geom::Vector& relativeMovement) :
	screenCoords(screenCoords), relativeMovement(relativeMovement) {}

bool MouseMotionData::operator<(const Data*) const {
	return false;
}

InputEvent::Data* MouseMotionData::clone() const {
	return new MouseMotionData(screenCoords, relativeMovement);
}
