#include <iostream>

// Functor type alias.
using Comparer = bool(*)(int, int);

// Functor.
bool IsGreater(int left, int right)
{
	return left > right;
}

bool IsLess(int left, int right)
{
	return left < right;
}

// 교환 함수.
void BubbleSort(int* array, int length, Comparer comparer)
{
	for (int ix = 0; ix < length - 1; ++ix)
	{
		for (int jx = 0; jx < length - 1 - ix; ++jx)
		{
			// Compare.
			if (comparer(array[jx], array[jx + 1]))
			{
				// swap.
				std::swap<int>(array[jx], array[jx + 1]);
			}
		}
	}
}

// Print Function.
void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];
		if (ix < length - 1) std::cout << ", ";
	}
	std::cout << "\n";
}

int main()
{

	// 자료 집합.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// length of the array.
	int length = sizeof(array) / sizeof(array[0]);

	BubbleSort(array, length, IsGreater);
	PrintArray(array, length);
	 
	return 0;
}