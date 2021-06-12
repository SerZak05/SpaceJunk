#include "sceneevent.h"

SceneEvent::SceneEvent(Widget* newScene) : Event(SCENE_EVENT), mScene(newScene) {}

Widget* SceneEvent::getScene() const {
	return mScene;
}
