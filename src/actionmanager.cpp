#include "actionmanager.h"
#include "appcontroller.h"
#include "merrors.h"
#include <fstream>
#include <string>

#include "events/keyboarddata.h"
#include "events/mousebuttondata.h"

ActionManager* ActionManager::inst = nullptr;

ActionManager::ActionManager() {
	// subscribing for SDL_Event loop
	userEventLoop.subscribe(this);

	// config
	std::string configFileName = "keybind.yaml";
	auto m = loadConfig(configFileName);
	readConfig(m);


	/*InputEvent lmb_pressed;
	lmb_pressed.type = InputEventType::MOUSE_BUTTON_DOWN;
	InputEvent::Data* data = new MouseButtonData(true, MouseButtonData::LEFT_BUTTON);
	lmb_pressed.data = data;
	eventsToActions[lmb_pressed] = Action("UP", 1);

	InputEvent lmb_released;
	lmb_released.type = InputEventType::MOUSE_BUTTON_UP;
	InputEvent::Data* data2 = new MouseButtonData(false, MouseButtonData::LEFT_BUTTON);
	lmb_released.data = data2;
	eventsToActions[lmb_released] = Action("UP", 0);

	InputEvent rmb_pressed;
	rmb_pressed.type = InputEventType::MOUSE_BUTTON_DOWN;
	InputEvent::Data* data3 = new MouseButtonData(true, MouseButtonData::RIGHT_BUTTON);
	rmb_pressed.data = data3;
	eventsToActions[rmb_pressed] = Action("DOWN", 1);

	InputEvent rmb_released;
	rmb_released.type = InputEventType::MOUSE_BUTTON_UP;
	InputEvent::Data* data4 = new MouseButtonData(false, MouseButtonData::RIGHT_BUTTON);
	rmb_released.data = data4;
	eventsToActions[rmb_released] = Action("DOWN", 0);
	*/
}

void ActionManager::loop() {
	sf::Event e;
	while (Drawer::getInst()->mWindow.pollEvent(e)) { // pulling SDL_Event
		// converting SDL to InputEvent for further use
		InputEvent convertedEvent = convert(e);
		// if don`t know how to convert, continue
		if (convertedEvent.type == InputEventType::UNKNOWN) {
			continue;
		}
		// pushing into queue
		InputEvent* convertedEvent_ptr = new InputEvent(convertedEvent);
		userEventLoop.pushEvent(convertedEvent_ptr);
	}
	// pulling input events
	while (userEventLoop.pullEvent());
}

Action ActionManager::getAction(const std::string& t) const {
	if (!isActionActive(t)) {
		return Action(t, 0);
	}
	return actions.find(t)->second;
}

bool ActionManager::isActionActive(const std::string& t) const {
	return actions.find(t) != actions.end();
}

std::list<InputEventType> ActionManager::acceptTypes() const {
	return {
		InputEventType::MOUSE_BUTTON, 
		InputEventType::KEYBOARD,
	};
}

void ActionManager::processEvent(const InputEvent* ev) {
	//mErr::oerr() << "Processing event with type " << (int)ev->type << std::endl;
	//InputEvent key = eventToKey(ev);

	// checking if binding exists
	if (eventsToActions.find(*ev) == eventsToActions.end()) {
		mErr::oerr() << "No bindings to event!" << std::endl;
		return;
	}
	// copying binded action
	Action action = eventsToActions[*ev];
	
	// checking, if we need to activate or deactivate an action

	switch (ev->type) {
	case InputEventType::MOUSE_BUTTON:
	case InputEventType::KEYBOARD:
		bool state = ev->state;
		if (state) {
			//mErr::oerr() << "Action activated: " << action.getType() << std::endl;
			actions[action.getType()] = action;
		}
		else {
			//mErr::oerr() << "Action deactivated: " << action.getType() << std::endl;
			actions.erase(action.getType());
		}
		break;
	}
}

ActionManager* ActionManager::getInst() {
	if (inst == nullptr) {
		inst = new ActionManager();
	}
	return inst;
}


void ActionManager::readConfig(const std::map<Action, std::list<InputEvent>>& inputMap) {
	for (auto it = inputMap.begin(); it != inputMap.end(); ++it) {
		for (auto ev = it->second.begin(); ev != it->second.end(); ++ev) {
			eventsToActions[*ev] = it->first;
		}
	}
}

std::map<Action, std::list<InputEvent>> ActionManager::writeConfig() const {
	std::map<Action, std::list<InputEvent>> res;
	for (auto it = eventsToActions.begin(); it != eventsToActions.end(); ++it) {
		res[it->second].push_back(it->first);
	}
	return res;
}

#include "../yaml/Yaml.hpp"

std::map<Action, std::list<InputEvent>> ActionManager::loadConfig(const std::string& fileName) {
	std::map<Action, std::list<InputEvent>> res;
	Yaml::Node root;
	Yaml::Parse(root, fileName.c_str());

	Yaml::Node& buttons = root["Buttons"];


	for (Yaml::Iterator it = buttons.Begin(); it != buttons.End(); it++) {
		const std::string& actionType = (*it).first;
		Yaml::Node& events = (*it).second;
		if (!events.IsMap()) {
			mErr::oerr() << "Not a map!" << std::endl;
			continue;
		}

		Action currAction(actionType, 1);
		for (Yaml::Iterator ev_it = events.Begin(); ev_it != events.End(); ev_it++) {
			std::string eventTypeStr = (*ev_it).first;
			mErr::oerr() << eventTypeStr << std::endl;
			InputEvent ev_activate, ev_deactivate;
			//ev_activate.type = String_to_InputEventType(eventTypeStr);
			ev_activate.state = true;
			ev_deactivate.state = false;

			if (eventTypeStr == "MOUSE_BUTTON") {
				ev_activate.type = InputEventType::MOUSE_BUTTON;
				ev_deactivate.type = InputEventType::MOUSE_BUTTON;
				ev_activate.data = new MouseButtonData((*ev_it).second["button"].As<std::string>());
				ev_deactivate.data = new MouseButtonData((*ev_it).second["button"].As<std::string>());
			}
			else if (eventTypeStr == "KEYBOARD") {
				ev_activate.type = InputEventType::KEYBOARD;
				ev_deactivate.type = InputEventType::KEYBOARD;
				ev_activate.data = new KeyboardData((sf::Keyboard::Key)(*ev_it).second["key"].As<int>());
				ev_deactivate.data = new KeyboardData((sf::Keyboard::Key)(*ev_it).second["key"].As<int>());
			}
			else {
				//ev_activate.type = InputEventType::UNKNOWN;
				//ev_deactivate.type = InputEventType::UNKNOWN;
				continue;
			}

			res[currAction].push_back(ev_activate);
			res[currAction].push_back(ev_deactivate);
		}
	}
	return res;
}

/*readConfig(map<string, list<InputEvent>> conf) {
	// enum InputEventType {
	// KeyboardEvent::TYPE_ID, MouseEvent::TYPE_ID, 
	for (const auto& a : conf) {
		switch
		a.first, a.second
	}
}*/

