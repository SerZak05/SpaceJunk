#pragma once
#include <list>


/* An interface for things with children and one parent. */
class TreeNode {
public:
	virtual void update() = 0;
	void updateChildren();
	std::list<TreeNode*> children;
};