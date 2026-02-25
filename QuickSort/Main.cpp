#include <iostream>

// Partition
// : Select Pivot & Devide.
int Partition(int* array, int left, int right)
{
	// value to divide.
	int pivot = array[left];
	int low = left + 1;
	int high = right;

	// Divdie Process: Move left=>right, and right=>left
	while (low <= right)
	{
		// Move left =>right.
		// Find value larger than pivot. 
		while (low <= right && array[low] <= pivot)
		{
			++low;
		}


		// Move right=>left.
		// Find value less than pivot.
		while (high > left && array[high] >= pivot)
		{
			--high;
		}

		// Check if the indexes are crossed.
		if (low > high)
		{
			break;
		}

		// Swap low <=>high.
		std::swap<int>(array[low], array[high]);
	}

	// Swap pivot <=> Last element of Left Data Array
	// array[left]: current pivot. 
	std::swap<int>(array[left], array[high]);

	// return final pivot position.
	return high;
}


// Quick Sort Recursion.
void QuickSort(int* array, int left, int right)
{

	// Exit Condition
	if (left >= right)
	{
		return;
	}

	// Divide.
	int pivot = Partition(array, left, right);

	// Sort left array.
	QuickSort(array, left, pivot - 1);

	// Sort Right Array.
	QuickSort(array, pivot + 1, right);
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
	//int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };
	// 자료 집합 2.
	int array[] =
	{
		1, 58, 10, 20, 56, 63, 73, 5, 28, 37,
		80, 61, 82, 45, 11, 66, 83, 59, 22, 64,
		52, 89, 94, 76, 44, 40, 75, 2, 23, 57,
		92, 8, 41, 96, 15, 84, 35, 69, 54, 47,
		90, 24, 43, 74, 34, 85, 72, 95, 18, 17,
		98, 9, 29, 53, 27, 79, 39, 51, 31, 16,
		6, 97, 26, 100, 21, 48, 33, 60, 91, 19,
		30, 13, 71, 78, 87, 25, 81, 4, 42, 93,
		49, 12, 14, 7, 62, 77, 38, 99, 88, 50,
		32, 46, 70, 3, 86, 68, 36, 67, 55, 65
	};


	// Get array item count.
	int length = _countof(array);

	QuickSort(array, 0, length-1);

	PrintArray(array, length);


	return 0;
}