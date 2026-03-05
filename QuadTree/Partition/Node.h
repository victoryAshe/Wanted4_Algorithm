#pragma once

#include "Bounds.h"
#include <vector>

// Helper: delete memory.
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

// enum to clarify area.
enum class NodeIndex
{
	// 완전히 포함되는 4가지.
	TopLeft,
	TopRight,
	BottomLeft,
	BottomRight,

	// 경계선에 걸침.
	Straddling,

	// 영역을 벗어남.
	OutOfArea
};


// Node class composits Quad Tree.
class Node
{
public:
	Node(const Bounds& bounds, int depth = 0);
	~Node();

	void Insert(Node* node);

	// 질의 (Querty:물어보기)
	// bounds: 영역 test 요청 값.
	// possibleNodes: 전달된 영역을 관리할 가능성이 있는 node의 목록.
	void Query(
		const Bounds& bounds,
		std::vector <Node*>& possibleNodes
	);

	void Clear();

	// Getter.
	inline const Bounds& GetBounds() const { return bounds; }

	inline const std::vector<Node*>& Points() const { return points; }

	// 자식 노드.
	inline Node* TopLeft() const{ return  topLeft;  }
	inline Node* TopRight() const{ return topRight; }
	inline Node* BottomLeft() const { return  bottomLeft; }
	inline Node* BottomRight() const { return bottomRight; }

private:
	// 4분할 함수.
	bool SubDivide();

	// Check the area is divided.
	bool IsDivided();

	// 전달된 영역과 겹치는 영역을 반환.
	NodeIndex TestRegion(const Bounds& bounds);

	// 전달한 영역이 포함되거나 거치는 영역을 모두 구할 때 사용.
	std::vector<NodeIndex> GetQuads(const Bounds& bounds);

	// 자식 노드 정리.
	void ClearChildren();

private:
	// 현재 노드의 깊이.
	int depth = 0;

	// 현재 노드의 영역(Bounds).
	Bounds bounds;

	// 현재 영역에 포함된 Node(list).
	std::vector<Node*> points;

	// children nodes.
	Node* topLeft  = nullptr;
	Node* topRight = nullptr;
	Node* bottomLeft  = nullptr;
	Node* bottomRight = nullptr;
};