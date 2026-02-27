#include "Navigation/Node.h"
#include "Navigation/AStar.h"

#include <iostream>
#include <vector>
#include <Windows.h>


// Map.
// 0: Movable.
// 1: Non-movable.
// 2: start position.
// 3: destination position.
std::vector<std::vector<int>> grid =
{
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 3, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 2, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
};


void FindStartAndDest(
	const std::vector<std::vector<int>>& grid,
	Node*& outStartNode,
	Node*& outGoalNode);



int main()
{
	// Hide Cursor.
	CONSOLE_CURSOR_INFO info = {};
	info.dwSize = 1;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);

	// Find Start Position && Destination Position.
	Node* startNode = nullptr;
	Node* goalNode = nullptr;

	FindStartAndDest(grid, startNode, goalNode);

	// if fails to search.
	if (!startNode || !goalNode)
	{
		// 생성됐을 수 있는 Node 삭제.
		SafeDelete(startNode);
		SafeDelete(goalNode);

		// restore console (skip).
		return 0;
	}

	// Path Finding.
	AStar aStar;

	auto path = aStar.FindPath(startNode, goalNode, grid);

	// If succeed
	if (!path.empty())
	{
		std::cout << "\n경로 탐색 성공.\n";
		aStar.DisplayGridWithPath(grid, path);
	}

	// Failed to find path.
	else
	{
		std::cout << "\n경로 탐색 실패.\n";
	}

	// Free destination node memory
	SafeDelete(goalNode);

	// Clean-up Console (Skip).
	COORD coord = { 0,30 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return 0;
}


void FindStartAndDest(
	const std::vector<std::vector<int>>& grid,
	Node*& outStartNode,
	Node*& outGoalNode)
{
	for (int y = 0; y < static_cast<int>(grid.size()); ++y)
	{
		for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
		{
			// Exit Condition: found the path.
			if (outStartNode && outGoalNode)
			{
				break;
			}

			for (int x = 0; x < static_cast<int>(grid[0].size()); ++x)
			{
				// Exit Condition: found the path.
				if (outStartNode && outGoalNode)
				{
					break;
				}

				// Start Node.
				if (grid[y][x] == 2)
				{
					outStartNode = new Node(x, y);
					continue;
				}

				// Destination Node.
				if (grid[y][x] == 3)
				{
					outGoalNode = new Node(x, y);
					continue;
				}
			}
		}
	}
}