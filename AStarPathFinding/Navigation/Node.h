#pragma once

// The position for the console screen.
class Position
{
public:
	int x = 0;
	int y = 0;

	Position(int x, int y)
		:x(x), y(y)
	{
	}
};

class Node
{
public:
	Node(int x, int y, Node* parentNode = nullptr)
		:position(x, y), parentNode(parentNode)
	{
	}

	Position operator-(const Node& other) const
	{
		return Position(position.x - other.position.x, position.y - other.position.y);
	}

	bool operator==(const Node& other) const
	{
		return (position.x == other.position.x) && (position.y == other.position.y);
	}



public:
	// The node's position.
	Position position;

	// the cost from the start to this node.
	float gCost = 0.0f;

	// the expectedc cost from this node to the destination (Heuristic)
	float hCost = 0.0f;

	// Final Cost (gCost + hCost)
	float fCost = 0.0f;

	// Link for the parent node.
	Node* parentNode = nullptr;
};