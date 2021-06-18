#include "bullet.h"
#include "merrors.h"

Bullet::Bullet(Field* f, const Geom::Vector& pos, const Geom::Vector& vel, float lifetime, double mass) : 
	GameObject(f, pos, mass), lifetime(lifetime) {
	velocity = vel;
}

void Bullet::update(double delta) {
	lifetime -= delta;
	if (lifetime <= 0) {
		mParent->deleteChild_queue(this);
		return;
	}
	move(delta);
}

void Bullet::draw(Drawer* const d) const {
	d->setColor(200, 0, 0);
	Geom::Vector globalCoords = getGlobalCoords();
	d->drawCircle(globalCoords, 10);
	// mErr::oerr() << "Bullet drawn!" << std::endl;
}
