#include "gameobject.h"

GameObject::GameObject(HierarchyNode* f, const Geom::Vector& c, double m) : HierarchyNode(c, 0, 1, f), mass(m) {}
GameObject::~GameObject() {}

void GameObject::move(double delta) {
	velocity += currForce / mass;
	relPos += velocity * delta;
	currForce = Geom::NULL_VECTOR;
}

void GameObject::applyForce(const Geom::Vector& force) {
	currForce += force;
}

Geom::Vector GameObject::getVelosity() const {
	return velocity;
}
