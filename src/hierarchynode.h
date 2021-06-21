#pragma once
#include <unordered_set>
#include "drawer.h"


class HierarchyNode {
public:
	HierarchyNode(const Geom::Vector&, double begAzimut, double begScale, HierarchyNode* parent = nullptr);
	HierarchyNode(const HierarchyNode&);
	virtual ~HierarchyNode();
// Calls chidren's update and draw
// Must be called in inherited method too
	virtual void update(double delta);
	virtual void draw(Drawer* const) const;

// Hierarchy stuff
protected:
	std::unordered_set<HierarchyNode*> mChildren;
	HierarchyNode* mParent;

	HierarchyNode* getRoot();
	const HierarchyNode* getRoot() const;

	virtual HierarchyNode* clone() const;
	// Not safe methods, directly inserts/erases child
	void addChild(HierarchyNode*);
	void deleteChild(HierarchyNode*);

public:
	// Safe methods can be used within the update loop
	// Puts children in queue first
	void addChild_queue(HierarchyNode*);
	void deleteChild_queue(HierarchyNode*);
private:
	std::list<HierarchyNode*> toAdd, toDelete;

protected:
	Geom::Vector relPos;
	double relAzimut, relScale;
public:
	Geom::Vector getRelCoords() const;
	Geom::Vector getGlobalCoords() const;
	double getGlobalAzimut() const; // returns azimut in [-PI, PI)
	double getGlobalScale() const;
};