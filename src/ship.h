#pragma once
#include "gameobject.h"


class Ship : public GameObject {
public:
	Ship(Field*, const Geom::Vector&);
	~Ship();

	virtual void update(double delta);
	virtual void draw(Drawer* const) const;
private:
	float azimut = 0;
	float accerationStrength = 0.3;
	float torgueStrength = 0.001;
	float sideDragStrength = 1;
	float drag_multiplier = 0.01;

	// in seconds
	float reloadTime = 0.05;
	float currReloadTime = 0;
};