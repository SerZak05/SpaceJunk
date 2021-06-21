#include "hierarchynode.h"
#include "vector.h"

HierarchyNode::HierarchyNode(const Geom::Vector& v, double begAzimut, double begScale, HierarchyNode* parent) 
	: relPos(v), relAzimut(begAzimut), relScale(begScale), mParent(parent)
{}

HierarchyNode::HierarchyNode(const HierarchyNode& other) 
	: mParent(other.mParent), relPos(other.relPos), relAzimut(other.relAzimut), relScale(other.relScale) 
{
	for (auto it = other.mChildren.begin(); it != other.mChildren.end(); ++it) {
		HierarchyNode* newChild = (*it)->clone();
		addChild(newChild);
	}
}

HierarchyNode::~HierarchyNode() {
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {
		delete *it;
	}
}

HierarchyNode* HierarchyNode::getRoot() {
	if (mParent == nullptr) {
		return this;
	}
	return mParent->getRoot();
}

const HierarchyNode* HierarchyNode::getRoot() const
{
	if (mParent == nullptr) {
		return this;
	}
	return mParent->getRoot();
}

HierarchyNode* HierarchyNode::clone() const {
	// must be overriden to create object of another class
	return new HierarchyNode(*this);
}

void HierarchyNode::addChild(HierarchyNode* newChild) {
	mChildren.insert(newChild);
	newChild->mParent = this;
}

void HierarchyNode::deleteChild(HierarchyNode* child) {
	if (mChildren.find(child) == mChildren.end()) return;
	delete child;
	mChildren.erase(child);
}

void HierarchyNode::addChild_queue(HierarchyNode* child) {
	toAdd.push_back(child);
}

void HierarchyNode::deleteChild_queue(HierarchyNode* child) {
	toDelete.push_back(child);
}

void HierarchyNode::update(double delta) {
	//mErr::oerr() << "Update!" << std::endl;
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {
		(*it)->update(delta);
	}
	for (auto it = toAdd.begin(); it != toAdd.end(); ++it) {
		addChild(*it);
	}
	toAdd.clear();
	for (auto it = toDelete.begin(); it != toDelete.end(); ++it) {
		deleteChild(*it);
	}
	toDelete.clear();
}

void HierarchyNode::draw(Drawer* const d) const {
	for (auto it = mChildren.begin(); it != mChildren.end(); ++it) {
		(*it)->draw(d);
	}
}

Geom::Vector HierarchyNode::getRelCoords() const { return relPos; }

Geom::Vector HierarchyNode::getGlobalCoords() const {
	if (getRoot() == this) {
		return relPos;
	}
	Geom::Vector relPosRotated = relPos;
	relPosRotated.rotate(mParent->getGlobalAzimut());
	return mParent->getGlobalCoords() + relPosRotated;
}

double HierarchyNode::getGlobalAzimut() const {
	if (getRoot() == this) {
		return relAzimut;
	}
	double azimut = mParent->getGlobalAzimut() + relAzimut;
	if (azimut >= Geom::PI)
		azimut -= 2 * Geom::PI;
	else if (azimut < -Geom::PI)
		azimut += 2 * Geom::PI;
	return azimut;
}

