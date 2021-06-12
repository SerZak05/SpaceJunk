#include "ship.h"
#include "actionmanager.h"
#include "merrors.h"
#include "bullet.h"

Ship::Ship(Field* f, const Geom::Vector& c) : GameObject(f, c, 1000.0) {}

Ship::~Ship() {}

void Ship::update(double delta) {
	// Shooting

	if (ActionManager::getInst()->isActionActive("SHOOT_MAIN")) {
		if (currReloadTime <= 0) {
			Geom::Vector beg_vel;
			const Geom::Vector& target = mField->getTargetedCoords();
			beg_vel = (target - coords).norm() * 100;
			mField->add(new Bullet(mField, coords, beg_vel, 5));

			currReloadTime = reloadTime;
		}
		else {
			currReloadTime -= delta;
		}
	}

	// Moving
	float forward = ActionManager::getInst()->getAction("UP").getStrength();
	float backward = ActionManager::getInst()->getAction("DOWN").getStrength();
	float leftTurn = ActionManager::getInst()->getAction("LEFT").getStrength();
	float rightTurn = ActionManager::getInst()->getAction("RIGHT").getStrength();

	azimut += (rightTurn - leftTurn) * torgueStrength;
	if (azimut < 0)
		azimut += 2 * Geom::PI;
	else if (azimut > 2 * Geom::PI)
		azimut -= 2 * Geom::PI;

	Geom::Vector force;
	force += Geom::Vector(1, 0).rotate(azimut) * (forward - backward);
	applyForce(force);

	Geom::Vector drag;
	drag = -velocity * velocity.mag() * drag_multiplier;
	applyForce(drag);

	move(delta);
	//mErr::oerr() << velocity << std::endl;
}

void Ship::draw(Drawer* const d) const {
	d->setColor(200, 200, 0);
	d->drawRect(coords - Geom::Vector(10, 10), coords + Geom::Vector(10, 10));
	d->drawLine(coords, coords + Geom::Vector(20, 0).rotate(azimut));
}
