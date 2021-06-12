#pragma once
#include "gameobject.h"

class Bullet : public GameObject {
public:
	Bullet(Field*, const Geom::Vector& beg_pos, const Geom::Vector& beg_velocity, float lifetime, double mass = 0.1);

	virtual void update(double delta);
	virtual void draw(Drawer* const) const;
private:
	float lifetime;
};