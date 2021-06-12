#include "../actionmanager.h"
#include "inputevent.h"
#include "mousebuttondata.h"
#include "keyboarddata.h"
#include "mousemotiondata.h"

InputEvent ActionManager::convert(const sf::Event& e) {
	//mErr::oerr() << "Converting event with type " << e->type << std::endl;
	InputEvent res;
	if (e.type == sf::Event::MouseMoved) {
		res.type = InputEventType::MOUSE_MOTION;

		const sf::Event::MouseMoveEvent me = e.mouseMove;
		res.data = new MouseMotionData({ (double)me.x, (double)me.y });
		return res;
	}
	if (e.type == sf::Event::MouseButtonPressed || e.type == sf::Event::MouseButtonReleased) {
		// Mouse events
		res.type = InputEventType::MOUSE_BUTTON;

		const sf::Event::MouseButtonEvent& me = e.mouseButton;
		std::string buttonName;
		switch (me.button) {
		case sf::Mouse::Left:
			buttonName = "LEFT";
			break;
		case sf::Mouse::Middle:
			buttonName = "MIDDLE";
			break;
		case sf::Mouse::Right:
			buttonName = "RIGHT";
			break;
		}
		res.state = (e.type == sf::Event::MouseButtonPressed);
		res.data = new MouseButtonData(
			buttonName,
			Geom::Vector(me.x, me.y)
		);
		return res;
	}
	if (e.type == sf::Event::KeyPressed || e.type == sf::Event::KeyReleased) {
		// Keyboard events
		// TODO add modifiers checks
		res.type = InputEventType::KEYBOARD;
		const sf::Event::KeyEvent& ke = e.key;
		res.state = (e.type == sf::Event::KeyPressed);
		res.data = new KeyboardData(
			ke.code
		);
		return res;
	}
	if (e.type == sf::Event::Closed) {
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