#pragma once
#include "widget.h"
class ExitWidget : public Widget {
public:
	ExitWidget(UI*);
	void processEvent(const InputEvent*);
	std::list<InputEventType> acceptTypes() const;
};

