#include "field.h"
#include "ship.h"
#include "events/mousemotiondata.h"
#include "actionmanager.h"
#include "merrors.h"

Field::Field() : HierarchyNode({ 0, 0 }, 0, 1) {
	ActionManager::getInst()->userEventLoop.subscribe(this);
}

Field::~Field() {}

bool Field::contains(GameObject* const obj) const {
	return mChildren.find(obj) != mChildren.end();
}

bool Field::add(GameObject* const obj) {
	if (contains(obj)) {
		return false;
	}
	//toAdd.push_back(obj);
	addChild_queue(obj);
	return true;
}

bool Field::remove(GameObject* const obj) {
	if (!contains(obj)) {
		return false;
	}
	//toRemove.push_back(obj);
	deleteChild_queue(obj);
	return true;
}

bool Field::init() { 
	ActionManager::getInst()->userEventLoop.subscribe(this, InputEventType::MOUSE_MOTION);
	mChildren.insert(new Ship(this, Geom::Vector(100, 100)));
	return true;
}

/*void Field::update(double delta) {
	/*for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {
		(*it)->update(delta);
	}
	for (auto it = toAdd.begin(); it != toAdd.end(); ++it) {
		addChild(*it);
	}
	toAdd.clear();
	for (auto it = toRemove.begin(); it != toRemove.end(); ++it) {
		deleteChild(*it);
	}
	toRemove.clear();
	((HierarchyNode*)this)->HierarchyNode::update(delta);
}*/

/*void Field::draw(Drawer* const d) const {
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {
		(*it)->draw(d);
	}
}*/

void Field::processEvent(const InputEvent* e) {
	auto me = static_cast<const MouseMotionData*>(e->data);
	cursorPos = me->screenCoords;
}

Geom::Vector Field::getTargetedCoords() const {
	return cursorPos;
}
