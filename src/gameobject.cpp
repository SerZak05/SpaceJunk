#include "gameobject.h"

GameObject::GameObject(Field* f, const Geom::Vector& c, double m) : mField(f), coords(c), mass(m) {}
GameObject::~GameObject() {}

void GameObject::move(double delta) {
	velocity += currForce / mass;
	coords += velocity * delta;
	currForce = Geom::NULL_VECTOR;
}

void GameObject::applyForce(const Geom::Vector& force) {
	currForce += force;
}

Geom::Vector GameObject::getCoords() const { return coords; }

Geom::Vector GameObject::getVelosity() const {
	return velocity;
}
