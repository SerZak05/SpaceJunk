#pragma once
#include <SDL.h>
#include <list>
#include "eventloop.h"
#include "widget.h"
#include "event.h"

class Widget;

class UI : Subscriber<EventType, Event> {
public:
	bool init();
	void update();
	void cleanup();

	void processEvent(const Event*);
	std::list<EventType> acceptTypes() const;

	EventLoop<EventType, Event> eventLoop;
private:
	//std::list<Widget> mWidgets;
	Widget* currScene = nullptr;
};