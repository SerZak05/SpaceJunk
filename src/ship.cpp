#include "ship.h"
#include "actionmanager.h"
#include "merrors.h"
#include "bullet.h"

Ship::Ship(Field* f, const Geom::Vector& c) : GameObject(f, c, 1000.0) {
	ActionManager::getInst()->actionLoop.subscribe(this);
	mTurret = new Turret<Bullet>(this, { 30, 0 });
	mChildren.insert(mTurret);
}

Ship::~Ship() {}

void Ship::update(double delta) {
	// Shooting
	Field* mField = ((Field*)mParent);

	
	relAzimut += (turningRight - turningLeft) * torgueStrength;
	relAzimut = Geom::angleToNorm(relAzimut);

	// ship phys act
	Geom::Vector force;
	force += Geom::Vector(accerationStrength, 0).rotate(relAzimut) * (forwardMovement - backwardMovement);
	applyForce(force);


	/*Geom::Vector drag;
	drag = -velocity * velocity.mag() * drag_multiplier;
	applyForce(drag);*/
	move(delta);
	//mErr::oerr() << velocity << std::endl;
	this->HierarchyNode::update(delta);
}

void Ship::draw(Drawer* const d) const {
	d->setColor(200, 200, 0);
	d->drawRect(relPos - Geom::Vector(10, 10), relPos + Geom::Vector(10, 10));
	//d->drawLine(coords, coords + Geom::Vector(20, 0).rotate(azimut));
	d->loadImage("ship.png");
	d->loadImage("ship_firing.png");
	// Body
	sf::Sprite body;
	sf::Texture texture;
	sf::Image img;
	if (forwardMovement != 0) {
		img = d->getImage("ship_firing.png");
	}
	else {
		img = d->getImage("ship.png");
	}
	img.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(img);
	body.setTexture(texture);
	// Turret
	auto bounds = body.getLocalBounds();
	body.setOrigin(bounds.width / 2, bounds.height / 2);
	body.setPosition(relPos.x, relPos.y);
	body.setRotation(relAzimut / Geom::PI * 180);
	d->drawSprite(body);

	

	//d->drawRect(Rect(0f, 0f, angle, 100f))

	((HierarchyNode*)this)->HierarchyNode::draw(d);
}

void Ship::processEvent(const Action* action) {
	// Moving TODO map
	float strength = action->getStrength();
	if (action->getType() == "UP_ON") {
		// mErr::oerr() << "Moving forward!" << std::endl;
		forwardMovement = strength;
	}
	else if (action->getType() == "UP_OFF") {
		// mErr::oerr() << "Stop moving forward!" << std::endl;
		forwardMovement = 0;
	}
	else if (action->getType() == "DOWN_ON") {
		// mErr::oerr() << "Moving backward!" << std::endl;
		backwardMovement = strength;
	}
	else if (action->getType() == "DOWN_OFF") {
		// mErr::oerr() << "Stop moving backward!" << std::endl;
		backwardMovement = 0;
	}
	else if (action->getType() == "LEFT_ON") {
		turningLeft = strength;
	}
	else if (action->getType() == "LEFT_OFF") {
		turningLeft = 0;
	}
	else if (action->getType() == "RIGHT_ON") {
		turningRight = strength;
	}
	else if (action->getType() == "RIGHT_OFF") {
		turningRight = 0;
	}
}

std::list<std::string> Ship::acceptTypes() const {
	return {
		// Movement
		"UP_ON",
		"UP_OFF",
		"LEFT_ON",
		"LEFT_OFF",
		"RIGHT_ON",
		"RIGHT_OFF",
		"DOWN_ON",
		"DOWN_OFF",
	};
}
