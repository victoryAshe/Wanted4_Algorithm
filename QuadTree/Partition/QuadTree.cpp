#include "QuadTree.h"

QuadTree::QuadTree(const Bounds& bounds)
{
	// Create root node.
	root = new Node(bounds);
}

QuadTree::~QuadTree()
{
	// delete roote node.
	SafeDelete(root);
}

void QuadTree::Insert(Node* node)
{
	// Exception Handling.
	if (!node)
	{
		return;
	}

	root->Insert(node);
}

std::vector<Node*> QuadTree::Query(Node* queryNode)
{
	// Exception Handling.
	if (!queryNode)
	{
		return {};
	}

	// 겹침 가능성이 있는 영역 확인
	// rootNode로부터 Query => 가능성이 있는 영역은 전부 possibleNode에 추가됨.
	std::vector<Node*> possibleNodes;
	root->Query(queryNode->GetBounds(), possibleNodes);

	// 실제 겹치는 node들만 확인.
	std::vector<Node*> intersects;
	for (Node* const node : possibleNodes)
	{
		for (Node* const point : node->Points())
		{
			// 해당 node(point)의 영역이 질의한 node 영역과 겹치면, 
			if (point->GetBounds().Intersects(queryNode->GetBounds()))
			{
				intersects.emplace_back(point);
				continue;
			}
		}
	}

	// return: 겹치는 영역들의 목록.
	return intersects;

}

