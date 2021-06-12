#pragma once
#include <string>
#include "vector.h"


/*enum ActionType {
	NONE, UP, DOWN, LEFT, RIGHT
};*/


class Action {
public:
	Action() : mType("NONE"), mStrength(0) {}
	Action(const std::string& t, float strength) : mType(t), mStrength(strength) {};

	std::string getType() const { return mType; }
	float getStrength() const { return mStrength; }

	bool operator<(const Action&) const;
private:
	std::string mType;
	float mStrength;
};