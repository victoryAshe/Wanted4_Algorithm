#include "Node.h"

Node::Node(const Bounds& bounds, int depth)
	:bounds(bounds), depth(depth)
{
}

Node::~Node()
{
	// 정리.
	Clear();
}

void Node::Insert(Node* node)
{
	// Exception Handling.
	if (!node)
	{
		return;
	}

	// 겹치는 영역 확인.
	NodeIndex result = TestRegion(node->GetBounds());

	// 두 개 이상 영역에 겹치는 경우 현재 node에 추가.
	if (result == NodeIndex::Straddling)
	{
		points.emplace_back(node);
	}
	// 영역이 겹치지 않은 경우
	// 경우 1. 1개의 영역에만 포함.
	else if (result != NodeIndex::OutOfArea)
	{
		// SubDivide 호출 시 MaxDepth에 도달하지 않으면 분할 진행.
		if(SubDivide())
		{
			if (result == NodeIndex::TopLeft)
			{
				topLeft->Insert(node);
			}
			else if (result == NodeIndex::TopRight)
			{
				topRight->Insert(node);
			}
			else if (result == NodeIndex::BottomLeft)
			{
				bottomLeft->Insert(node);
			}
			else if (result == NodeIndex::BottomRight)
			{
				bottomRight->Insert(node);
			}
		}
		// 분할할 수 없는 경우(이미 최대 깊이에 도달)
		else
		{
			points.emplace_back(node);
		}
	}

	// 경우 2. 영역 밖에 있는 경우 (OutOfArea).
	// 아무 처리 안함(노드 추가 안함)

}

void Node::Query(const Bounds& bounds, std::vector<Node*>& possibleNodes)
{
	// 현재 노드를 추가하고 이후 과정 진행.
	possibleNodes.emplace_back(this);

	// 분할 여부 확인 후 자손 검사.
	if (!IsDivided())
	{
		return;
	}

	// 전달받은 영역과 겹치는 4분면 목록 확인.
	std::vector<NodeIndex> quads = GetQuads(bounds);

	// 검사 진행.
	for (const NodeIndex& index : quads)
	{
		if (index == NodeIndex::TopLeft)
		{
			topLeft->Query(bounds, possibleNodes);
		}
		else if (index == NodeIndex::TopRight)
		{
			topRight->Query(bounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomLeft)
		{
			bottomLeft->Query(bounds, possibleNodes);
		}
		else if (index == NodeIndex::BottomRight)
		{
			bottomRight->Query(bounds, possibleNodes);
		}
	}
}

void Node::Clear()
{
	// points에 있는 node들은 외부(Level)에서 관리하는 node이므로,
	// node에서 따로 memory management(delete) 안함.

	// 목록만 정리.
	points.clear();

	// 분할된 경우, 자손 정리.
	if (IsDivided())
	{
		topLeft->Clear();
		topRight->Clear();
		bottomLeft->Clear();
		bottomRight->Clear();

		ClearChildren();
	}

}

bool Node::SubDivide()
{
	// 최대 깊이에 도달했는지 확인.
	// @InComplete: 임시로 하드코딩 값 설정.
	// TODO: depth를 QuadTree에서 받기.
	// 이미 최대로 분할됨.
	if (depth == 5)
	{
		return false;
	}

	// 분할 여부 파악.
	// 분할 전이면 영역 나누기.
	if (!IsDivided())
	{
		// variables to divide the area.
		int x = bounds.X();
		int y = bounds.Y();
		int halfWidth = bounds.Width() / 2;
		int halfHeight = bounds.Height() / 2;

		// Create children nodes for 4 side.
		topLeft = new Node(
			Bounds(x, y, halfWidth, halfHeight), depth + 1
		);

		topRight = new Node(
			Bounds(x + halfWidth, y, halfWidth, halfHeight), depth + 1
		);
		
		bottomLeft = new Node(
			Bounds(x, y + halfHeight, halfWidth, halfHeight), depth + 1
		);

		bottomRight = new Node(
			Bounds(x + halfWidth, y + halfHeight, halfWidth, halfHeight), depth + 1
		);
	}

	return true;
}

bool Node::IsDivided()
{
	// 분할이 됐다면, 모든 자식 노드가 null이 아님
	// => 하나의 자식 노드만 확인하면 됨!
	return topLeft != nullptr;
}

NodeIndex Node::TestRegion(const Bounds& bounds)
{
	// 전달된 bounds와 겹치는 4분면 목록을 확인.
	std::vector<NodeIndex> quads = GetQuads(bounds);

	// 겹치는 곳이 없으면 OutOfArea 반환.
	if (quads.empty())
	{
		return NodeIndex::OutOfArea;
	}

	// 4개 중 하나의 영역에만 겹치는 경우 해당 4분면 반환.
	if (quads.size() == 1)
	{
		return quads[0];
	}

	// 여러 영역과 겹친 경우.
	return NodeIndex::Straddling;
}

std::vector<NodeIndex> Node::GetQuads(const Bounds& bounds)
{
	// 겹치는 영역 반환을 위한 변수.
	std::vector<NodeIndex> quads;

	// 영역 계산에 필요한 변수.
	int x = this->bounds.X();
	int y = this->bounds.Y();
	int halfWidth = this->bounds.Width() / 2;
	int halfHeight = this->bounds.Height() / 2;
	int centerX = x + halfWidth;
	int centerY = y + halfHeight;

	// 왼쪽 영역과 겹치는지 확인.
	bool left =
		bounds.X() < centerX && bounds.X() < this->bounds.MaxX();

	// 위쪽 영역과 겹치는지 확인.
	bool right
		= bounds.MaxX() >= centerX && bounds.X() < this->bounds.MaxX();

	bool top
		= bounds.Y() < centerY && bounds.MaxY() >= y;

	bool bottom
		= bounds.MaxY() >= centerY && bounds.Y() < this->bounds.MaxY();

	// 영역 판정.
	if (top && left)
	{
		quads.emplace_back(NodeIndex::TopLeft);
	}
	if (top && right)
	{
		quads.emplace_back(NodeIndex::TopRight);
	}
	if (bottom && left)
	{
		quads.emplace_back(NodeIndex::BottomLeft);
	}

	if (bottom && right)
	{
		quads.emplace_back(NodeIndex::BottomRight);
	}


	return quads;
}

void Node::ClearChildren()
{
	// 분할 진행된 경우, 자손 노드 삭제.
	if (IsDivided())
	{
		SafeDelete(topLeft);
		SafeDelete(topRight);
		SafeDelete(bottomLeft);
		SafeDelete(bottomRight);
	}
}
