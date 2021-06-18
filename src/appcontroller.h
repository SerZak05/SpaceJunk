#pragma once
#include "drawer.h"
#include "ui.h"

class UI;

class AppController : Subscriber<InputEventType, InputEvent> {
public:
	static AppController* getInst();
	static void cleanup();

	void run();
	void stop();

	void processEvent(const InputEvent*);
	std::list<InputEventType> acceptTypes() const;

	// UI ui;
private:
	AppController();
	~AppController();
	bool init();

	static AppController* inst;

	bool Running = false;
};