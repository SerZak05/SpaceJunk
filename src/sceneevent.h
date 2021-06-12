#pragma once
#include "event.h"
#include "widget.h"


class SceneEvent : public Event {
public:
	SceneEvent(Widget* newScene);
	Widget* getScene() const;

private:
	Widget* mScene;
};