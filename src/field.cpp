#include "field.h"
#include "ship.h"
#include "events/mousemotiondata.h"
#include "actionmanager.h"

Field::Field() {
	ActionManager::getInst()->userEventLoop.subscribe(this);
}

Field::~Field() {
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
		delete (*it);
	}
}

bool Field::contains(GameObject* const obj) const {
	return mObjects.find(obj) != mObjects.end();
}

bool Field::add(GameObject* const obj) {
	if (contains(obj)) {
		return false;
	}
	toAdd.push_back(obj);
	return true;
}

bool Field::remove(GameObject* const obj) {
	if (!contains(obj)) {
		return false;
	}
	toRemove.push_back(obj);
	return true;
}

bool Field::init() { 
	mObjects.insert(new Ship(this, Geom::Vector(100, 100)));
	return true;
}

void Field::loop(double delta) {
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
		(*it)->update(delta);
	}
	for (auto it = toAdd.begin(); it != toAdd.end(); ++it) {
		mObjects.insert(*it);
	}
	toAdd.clear();
	for (auto it = toRemove.begin(); it != toRemove.end(); ++it) {
		mObjects.erase(*it);
		delete (*it);
	}
	toRemove.clear();
}

void Field::draw(Drawer* const d) const {
	for (auto it = mObjects.begin(); it != mObjects.end(); ++it) {
		(*it)->draw(d);
	}
}

void Field::processEvent(const InputEvent* e) {
	auto me = static_cast<const MouseMotionData*>(e->data);
	cursorPos = me->screenCoords;
}

Geom::Vector Field::getTargetedCoords() const {
	return cursorPos;
}
