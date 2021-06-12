#pragma once
#include <list>
#include <unordered_set>
#include "gameobject.h"
#include "drawer.h"
#include "subscriber.h"
#include "events/inputevent.h"

class GameObject;

class Field : public Subscriber<InputEventType, InputEvent> {
public:
	Field();
	~Field();

	bool contains(GameObject* const) const;
	//deletes the object entirely
	bool remove(GameObject* const); //true - it was contained, false - otherwise
	bool add(GameObject* const);	//false - it was contained, true - otherwise

	bool init();
	void loop(double delta);

	void draw(Drawer* const) const;

	std::list<InputEventType> acceptTypes() const { return { InputEventType::MOUSE_MOTION }; }
	void processEvent(const InputEvent*);

	Geom::Vector getTargetedCoords() const;

private:
	std::unordered_set<GameObject*> mObjects;
	std::list<GameObject*> toAdd;
	std::list<GameObject*> toRemove;

	Geom::Vector cursorPos;
};