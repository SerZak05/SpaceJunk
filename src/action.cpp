#include "action.h"

bool Action::operator<(const Action& action) const {
	if (mType != action.getType())
		return mType < action.getType();
	return mStrength < action.getStrength();
}
