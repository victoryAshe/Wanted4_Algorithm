#pragma once

#include "Node.h"

#include <vector>

template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}


class AStar
{
	// struct for process direction.
	struct Direction
	{
		// position.
		int x = 0;
		int y = 0;

		// cost to move.
		float cost = 0.0f;
	};


public:
	AStar();
	~AStar();

	// OOP => Message: public member function(Interface)
	// PathFinding.
	std::vector<Node*> FindPath(
		Node* startNode, Node* goalNode,		// Start, Destination.
		std::vector<std::vector<int>>& grid		// Grid: 2D array to search.
	);

	// Print Grid.
	void DisplayGridWithPath(
		std::vector<std::vector<int>>& grid,
		const std::vector<Node*>& path
	);

private:
	// OOP => Method: private member function.
	
	// return the best-path after complete finding.
	// back-tracking follow the parent node.
	std::vector<Node*> ConstructPath(Node* goalNode);

	// Calculate hCost.
	float CalculateHeuristic(Node* currentNode, Node* goalNode);

	// Check next node is in valid range.
	// Valid Check.
	bool IsInRange(int x, int y, const std::vector<std::vector<int>>& grid);

	// Check already visited.
	bool HasVisited(int x, int y, float gCost);

	// Check next node is the destination node.
	bool IsDestination(const Node* node);

	// Print Grid.
	void DisplayGrid(std::vector<std::vector<int>>& grid);

private:
	// opened list.
	std::vector<Node*> openList;

	// closed list.
	std::vector<Node*> closedList;
	
	// start node.
	Node* startNode = nullptr;

	// destination node.
	Node* goalNode = nullptr;
};

