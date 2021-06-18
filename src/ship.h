#pragma once
#include "gameobject.h"
#include "turret.h"
#include "bullet.h"


class Ship : public GameObject, public Subscriber<std::string, Action> {
public:
	Ship(Field*, const Geom::Vector&);
	~Ship();

	virtual void update(double delta);
	virtual void draw(Drawer* const) const;

	void processEvent(const Action*);
	std::list<std::string> acceptTypes() const;
private:
	// float azimut = 0;
	float accerationStrength = 100;
	float torgueStrength = 0.01;
	float sideDragStrength = 1;
	float drag_multiplier = 0.01;

	float forwardMovement = 0;
	float backwardMovement = 0;
	float turningLeft = 0;
	float turningRight = 0;

	Turret<Bullet>* mTurret;
};