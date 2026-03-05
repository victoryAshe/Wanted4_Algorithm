#pragma once

// 사각형 영역을 표시하는 클래스.
class Bounds
{
public:
	Bounds(int x, int y, int width = 1, int height = 1)
		: x(x), y(y), width(width), height(height)
	{
	}

	// Getter.
	inline int X() const { return x; }
	inline int Y() const { return y; }
	inline int Width() const { return width; }
	inline int Height() const { return height; }

	inline int MaxX() const { return x + width; }
	inline int MaxY() const { return y + height; }

	// 겹침 판정 함수
	// AABB.
	bool Intersects(const Bounds& other) const;

private:
	// 왼쪽 상단 지점을 기준으로 위치 표시.
	int x = 0;
	int y = 0;

	// 너비/높이.
	// 상용 Engine은 float 좌표를 쓰지만, Console 좌표는 int를 쓰므로 int로 설정.
	int width = 1;
	int height = 1;

};

