#pragma once
#include <list>
#include "common.h"
#include "subscriber.h"
#include "drawer.h"
#include "ui.h"
#include "events/inputevent.h"

class UI;

enum WidgetFlag {
	DRAGGABLE = 1,
	SCALABLE = 2,
	SHOWN = 4,
	ACTIVE = 8
};


class Widget : public Subscriber<InputEventType, InputEvent> {
public:
	Widget(UI*);
	virtual ~Widget();
	void processEvent(const InputEvent*);
	std::list<InputEventType> acceptTypes() const;
	std::list<Widget*> children;

	int getFlags() const;
	void setFlagToTrue(WidgetFlag);
	void setFlagToFalse(WidgetFlag);
	void toggleFlag(WidgetFlag);

	virtual void update();

	virtual void draw(Drawer*) const;

	virtual void cleanup();
protected:
	UI* ui;
private:
	int flags = 0;
};

