#pragma once
#include <unordered_map>
#include <vector>
#include <array>
#include <map>
#include <SFML/Window/Event.hpp>
#include "action.h"
#include "subscriber.h"
#include "events/inputevent.h"
#include "eventloop.h"

/*typedef SDL_KeyboardEvent KeyboardEvent;
typedef SDL_Event InputEvent;
typedef SDL_EventType InputEventType;
typedef SDL_MouseButtonEvent MouseButtonEvent;
typedef SDL_MouseMotionEvent MouseMotionEvent;*/


class ActionManager : public Subscriber<InputEventType, InputEvent> {
public:
	// processes events from player
	void loop();

	// gets the data of the action of that type
	// Action getAction(const std::string&) const;
	// checks, if specific type of action is active
	// bool isActionActive(const std::string&) const;

	/// Subscriber methods
	virtual std::list<InputEventType> acceptTypes() const;
	virtual void processEvent(const InputEvent*);

	static ActionManager* getInst();
	//void readConfig(std::unordered_map<std::string, InputEvent>);

	// static getKeySpec
	/// source of config

	// source eventloop
	EventLoop<InputEventType, InputEvent> userEventLoop;

	EventLoop<std::string, Action> actionLoop;

	void addAction(Action*);
	
private:
	ActionManager();
	static ActionManager* inst;

	// Event -> Action ('w' on keyboard event -> UP action)
	std::map<InputEvent, Action, InputEvent::Comp> eventsToActions;
	// Active actions
	// std::unordered_map<std::string, Action> actions;

	// constructs new InputEvent out of SDL_Event for later use
	static InputEvent convert(const sf::Event&);

	// reads config map (action -> list of events to activate) and builds eventsToActions map
	void readConfig(const std::map<Action, std::list<InputEvent>>&);
	// saves eventsToAction map into config map (action -> events to activate)
	std::map<Action, std::list<InputEvent>> writeConfig() const;
	// loads config map (action -> list of events to activate) from file
	static std::map<Action, std::list<InputEvent>> loadConfig(const std::string& fileName);
};