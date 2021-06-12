#include "../actionmanager.h"
#include "inputevent.h"
#include "mousebuttondata.h"
#include "keyboarddata.h"
#include "mousemotiondata.h"

InputEvent ActionManager::convert(const SDL_Event* e) {
	//mErr::oerr() << "Converting event with type " << e->type << std::endl;
	InputEvent res;
	if (e->type == SDL_MOUSEMOTION) {
		res.type = InputEventType::MOUSE_MOTION;

		const SDL_MouseMotionEvent me = e->motion;
		res.data = new MouseMotionData({ (double)me.x, (double)me.y }, { (double)me.xrel, (double)me.yrel });
		return res;
	}
	if (e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
		// Mouse events
		res.type = InputEventType::MOUSE_BUTTON;

		const SDL_MouseButtonEvent& me = e->button;
		std::string buttonName;
		switch (me.button) {
		case SDL_BUTTON_LEFT:
			buttonName = "LEFT";
			break;
		case SDL_BUTTON_MIDDLE:
			buttonName = "MIDDLE";
			break;
		case SDL_BUTTON_RIGHT:
			buttonName = "RIGHT";
			break;
		}
		res.state = (bool)me.state;
		res.data = new MouseButtonData(
			buttonName,
			Geom::Vector(me.x, me.y)
		);
		return res;
	}
	if (e->type == SDL_KEYDOWN || e->type == SDL_KEYUP) {
		// Keyboard events
		// TODO add modifiers checks
		res.type = InputEventType::KEYBOARD;
		const SDL_KeyboardEvent& ke = e->key;
		res.state = (bool)ke.state;
		res.data = new KeyboardData(
			(char)ke.keysym.sym
		);
		return res;
	}
	if (e->type == SDL_QUIT) {
		// Quit event (clicking on the cross in the corner)
		res.type = InputEventType::QUIT;
		res.data = nullptr;
		return res;
	}
	//mErr::oerr() << "Unknown event occured! " << e->type << std::endl;

	// if unknown event occurs, we mark it
	res.type = InputEventType::UNKNOWN;
	res.data = nullptr;
	return res;
}