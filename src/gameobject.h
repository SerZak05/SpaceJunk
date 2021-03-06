#pragma once
#include "vector.h"
#include "field.h"
#include "drawer.h"
#include "hierarchynode.h"

class Field;

class GameObject : public HierarchyNode {
public:
	GameObject(HierarchyNode*, const Geom::Vector& c = { 0, 0 }, double mass = 1);
	virtual ~GameObject();

	virtual void update(double delta) = 0;
	virtual void draw(Drawer* const) const = 0;

	void applyForce(const Geom::Vector& force);

	Geom::Vector getVelosity() const;
protected:
	double mass;
	Geom::Vector velocity;
	Geom::Vector currForce;

	// updates object`s motion (if needed in derived)
	void move(double delta);
};