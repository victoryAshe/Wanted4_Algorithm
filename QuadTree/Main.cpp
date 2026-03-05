#include "Partition/QuadTree.h"
#include <iostream>

// simple class.
class Level
{
public:
	Level() = default;
	~Level()
	{
		// Level에 배치된 모든 Node 제거.
		for (Node*& node : nodeList)
		{
			SafeDelete(node);
		}

		// 목록 정리.
		nodeList.clear();
	}

	// Level에 새로운 node 추가.
	void AddNewNode(Node* newNode)
	{
		nodeList.emplace_back(newNode);
	}

	// Getter.
	inline const std::vector<Node*>& GetAllNodes() const { return nodeList; }
	
private:
	// Level에 배치된 node의 list. (Actor로 생각해볼 수 있다).
	std::vector<Node*> nodeList;
};

int main()
{
	// Level 구성.
	Level level;
	level.AddNewNode(new Node(Bounds(60, 80)));
	level.AddNewNode(new Node(Bounds(50, 50)));
	level.AddNewNode(new Node(Bounds(90, 120)));
	level.AddNewNode(new Node(Bounds(150, 150)));
	level.AddNewNode(new Node(Bounds(10, 10)));

	// Tree 구성.
	// (0,0) 좌표를 왼쪽 상단 지점으로 취함.
	QuadTree tree(Bounds(0, 0, 200, 200));

	// 삽입.
	for (Node* node : level.GetAllNodes())
	{
		tree.Insert(node);
	}

	std::cout << "[Node 삽입 완료]\n";

	// 질의(Query).
	//Node testNode(Bounds(10, 10));
	Node testNode(Bounds(45, 45, 20, 40));
	//Node testNode(Bounds(10, 120));
	std::vector<Node*> intersects = tree.Query(&testNode);


	// 검색 성공.
	if (!intersects.empty())
	{
		std::cout << "겹치는 Node를 " << intersects.size() << "개 찾았습니다.\n";
	}

	// 검색 실패.
	else
	{
		std::cout << "겹치는 Node를 찾지 못했습니다.\n";
	}


	return 0;
}