#include <iostream>

// 배열을 힙으로 만드는 함수.
void Heapify(int* array, int length, int index)
{
	// keep Recursion until complete composite heap.
	while (true)
	{
		// MaxHeap
		int largest = index;

		// Get child index
		// Left Child Index: 2N+1, Right Child Index: 2N+2
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;

		//Find the bigger one. + Valid Check.
		if (leftChild < length
			&& array[leftChild] > array[largest])
		{
			largest = leftChild;
		}

		//Find the bigger one. + Valid Check.
		if (rightChild < length
			&& array[rightChild] > array[largest])
		{
			largest = rightChild;
		}


		// Exit contidion: if current node is largest.
		if (largest == index)
		{
			break;
		}

		// Swap: Current Node <=> Largest Node.
		std::swap<int>(array[index], array[largest]);

		// Update largest as the index.
		index = largest;
	}                                                                                                                                                                      
}

// HeapSort Function.
void HeapSort(int* array, int length)
{
	// Transform array => Heap
	for (int ix = length / 2 - 1; ix >= 0; --ix)
	{
		Heapify(array, length, ix);
	}

	// Heap Sort.
	for (int ix = length - 1; ix > 0; --ix)
	{
		// Swap: Root Node <=> Crrunt Node(the last node)
		// because: current node is already used for sorting.
		std::swap<int>(array[0], array[ix]);

		// Re-Heapify: 힙 구조를 유지하기 위함.
		//Heapify(array, length, ix);
		Heapify(array, ix, 0);
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
	int array[] = { 5, 2, 8, 4, 1, 7, 3, 6, 9, 10, 15, 13, 14, 12, 17, 16 };
	//int array[] =
	//{
	//	1, 58, 10, 20, 56, 63, 73, 5, 28, 37,
	//	80, 61, 82, 45, 11, 66, 83, 59, 22, 64,
	//	52, 89, 94, 76, 44, 40, 75, 2, 23, 57,
	//	92, 8, 41, 96, 15, 84, 35, 69, 54, 47,
	//	90, 24, 43, 74, 34, 85, 72, 95, 18, 17,
	//	98, 9, 29, 53, 27, 79, 39, 51, 31, 16,
	//	6, 97, 26, 100, 21, 48, 33, 60, 91, 19,
	//	30, 13, 71, 78, 87, 25, 81, 4, 42, 93,
	//	49, 12, 14, 7, 62, 77, 38, 99, 88, 50,
	//	32, 46, 70, 3, 86, 68, 36, 67, 55, 65
	//};

	// Get Array length
	int length = _countof(array);

	HeapSort(array, length);

	PrintArray(array, length);

	return 0;
}