#include "ui.h"
#include "exitwidget.h"
#include "sceneevent.h"

bool UI::init() {
	bool success = true;
	//mSceneEventLoop.subscribe(this, SCENE_EVENT);
	currScene = new Widget(this);
	currScene->children.push_back(new ExitWidget(this));
	return success;
}

void UI::update() {
	while (eventLoop.pullEvent());
	if (currScene != nullptr)
		currScene->update();
}

void UI::cleanup() {
	currScene->cleanup();
	delete currScene;
}

std::list<EventType> UI::acceptTypes() const {
	return {SCENE_EVENT};
}

void UI::processEvent(const Event* ev) {
	const SceneEvent* sceneEv = static_cast<const SceneEvent*>(ev);
	currScene->cleanup();
	delete currScene;
	currScene = sceneEv->getScene();
}