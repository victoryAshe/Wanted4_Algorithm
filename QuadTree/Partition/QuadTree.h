#pragma once

#include "Node.h"

class QuadTree
{
public:
	QuadTree(const Bounds& bounds);
	~QuadTree();

	// Add Node to the tree.
	void Insert(Node* node);

	std::vector<Node*> Query(Node* queryNode);

public:
	// Tree의 최대 허용 깊이.
	static const int maxDepth = 5;

private:
	// root node.
	Node* root = nullptr;

};

