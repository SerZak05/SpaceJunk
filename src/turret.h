#pragma once
#include "gameobject.h"
#include "game.h"
#include "merrors.h"
#include "common.h"


template<class BulletType>
class Turret : public GameObject, public Subscriber<std::string, Action> {
public:
	Turret(Field* parent, const Geom::Vector& relPos);
	Turret(GameObject* parent, const Geom::Vector& relPos);

	virtual void update(double delta);
	virtual void draw(Drawer* const) const;

	// derived from Subscriber
	inline std::list<std::string> acceptTypes() const;
	void processEvent(const Action*);
private:
	void init();

	void shoot();

	Geom::Vector emitter;
	double rotationSpeed = 0.005; // in radians
	double currReloadTime = 0, reloadTime = 1;

	bool shooting = false;

};

template<class BulletType>
inline Turret<BulletType>::Turret(Field* parent, const Geom::Vector& relPos) 
	: GameObject(parent, relPos)
{
	init();
}

template<class BulletType>
inline Turret<BulletType>::Turret(GameObject * parent, const Geom::Vector & relPos) 
	: GameObject(parent, relPos)
{
	init();
}

template<class BulletType>
inline void Turret<BulletType>::init() {
	ActionManager::getInst()->actionLoop.subscribe(this);
	Drawer::getInst()->loadImage("turret.png");
	Drawer::getInst()->loadImage("turret_firing.png");

	emitter = Geom::Vector(0, 100);
}

template<class BulletType>
inline void Turret<BulletType>::update(double delta) {
	if (shooting) {
		if (currReloadTime <= 0) {
			shoot();
		}
		else {
			currReloadTime -= delta;
		}
	}

	// Turning the turret
	double targetAngle = (((Field*)getRoot())->getTargetedCoords() - getGlobalCoords()).azimut();
	double deltaAngle = Geom::angleToNorm(targetAngle - getGlobalAzimut());
	if (deltaAngle > rotationSpeed)
		relAzimut += rotationSpeed;
	else if (deltaAngle < -rotationSpeed)
		relAzimut -= rotationSpeed;
	else
		relAzimut += deltaAngle;

	relAzimut = Geom::angleToNorm(relAzimut);

	// mErr::oerr() << relAzimut << std::endl;

	this->HierarchyNode::update(delta);
}

template<class BulletType>
inline void Turret<BulletType>::draw(Drawer* const d) const {
	sf::Sprite turret;
	sf::Image img;
	sf::Texture texture;
	if (shooting) {
		img = d->getImage("turret_firing.png");
	}
	else {
		img = d->getImage("turret.png");
	}
	img.createMaskFromColor(sf::Color(255, 255, 255));
	texture.loadFromImage(img);
	turret.setTexture(texture);

	auto bounds = turret.getLocalBounds();
	turret.setOrigin(bounds.height / 2, bounds.height / 2);
	turret.setPosition(getGlobalCoords().x, getGlobalCoords().y);
	//float angle = (((Field*)mParent)->getTargetedCoords() - relPos).azimut() / Geom::PI * 180;
	turret.setRotation(-getGlobalAzimut() / Geom::PI * 180 + 90);
	d->drawSprite(turret);

	this->HierarchyNode::draw(d);
}

template<class BulletType>
inline std::list<std::string> Turret<BulletType>::acceptTypes() const
{
	return { 
		"SHOOT_MAIN_ON", 
		"SHOOT_MAIN_OFF"
	};
}

template<class BulletType>
inline void Turret<BulletType>::processEvent(const Action* action) {
	if (action->getType() == "SHOOT_MAIN_ON") {
		shooting = true;
	}
	else if (action->getType() == "SHOOT_MAIN_OFF") {
		shooting = false;
	}
}

template<class BulletType>
inline void Turret<BulletType>::shoot() {
	Geom::Vector beg_vel = Geom::NORTH_VECTOR, beg_pos = emitter;
	beg_vel.rotate(-getGlobalAzimut());
	beg_pos.rotate(-getGlobalAzimut());
	beg_pos += getGlobalCoords();
	beg_vel *= 100;
	Field* field = (Field*)getRoot();
	field->add(new BulletType(field, beg_pos, beg_vel, 5));
	mErr::oerr() << "Shooting!" << std::endl;
	// ActionManager::getInst()->addAction(new CreateGameObjectAction(new BulletType)
	currReloadTime = reloadTime;
}
