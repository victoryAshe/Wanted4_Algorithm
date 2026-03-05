#include "Bounds.h"

bool Bounds::Intersects(const Bounds& other) const
{
	// 겹치지 않은 경우 먼저 판단.

	// 다른 영역이 오른쪽으로 벗어난 경우.
	if (other.x > MaxX())
	{
		return false;
	}

	// 다른 영역이 왼쪽으로 벗어난 경우.
	if (other.MaxX() < x)
	{
		return false;
	}

	// 다른 영역이 아래로 벗어난 경우.
	if (other.y > MaxY())
	{
		return false;
	}

	// 다른 영역이 위로 벗어난 경우.
	if (other.MaxY() < y)
	{
		return false;
	}

	// 위에서 걸리지 않음 => 겹침
	return true;
}
