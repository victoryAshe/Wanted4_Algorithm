#include <iostream>
#include <Windows.h>

void InsertionSort(int* array, int length)
{
	// Exception Handling.
	if (length <= 1)
	{
		return;
	}


	// Rounding the array.
	for (int ix = 1; ix < length; ++ix)
	{
		int key = array[ix];
		int jx = ix - 1;
 
		// key보다 큰 값은 오른쪽으로 배치.
		while (jx>=0 && array[jx] > key)
		{
			array[jx + 1] = array[jx];
			--jx;
		}

		// Insert key at the correct Location.
		array[jx + 1] = key;
	}
}


// 출력 함수.
void PrintArray(int* array, int length)
{
	for (int ix = 0; ix < length; ++ix)
	{
		std::cout << array[ix];

		// 마지막 원소 전까지는 콤마 출력.
		if (ix < length - 1)
		{
			std::cout << ", ";
		}
	}

	std::cout << "\n";
}

int main()
{

	// 자료 집합.
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };

	// Get the item count of the array.
	// at the Windows header.
	//int length = ARRAYSIZE(array);
	int length = _countof(array);

	//PrintArray(array, length);
	InsertionSort(array, length);
	PrintArray(array, length);



	return 0;
}