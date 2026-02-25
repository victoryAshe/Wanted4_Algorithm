#include <iostream>

// Merge
// Difficult to simulate.
void Merge(
	int* array,
	int* leftArray, int leftArrayLength,
	int* rightArray, int rightArrayLength
)
{
	// Declare indexes.
	int leftIndex = 0;
	int rightIndex = 0;
	int mergedIndex = 0;

	// Compare the left/right array element 
	// => copy smaller element of array to origin array.
	while (leftIndex < leftArrayLength
		&& rightIndex < rightArrayLength)
	{
		if (leftArray[leftIndex] <= rightArray[rightIndex])
		{
			array[mergedIndex] = leftArray[leftIndex];
			++leftIndex;
		}
		else // if the right array's element is smaller:
		{
			array[mergedIndex] = rightArray[rightIndex];
			++rightIndex;
		}

		// Add Process: merged Array Index.
		++mergedIndex;
	}

	// 위의 과정에서 왼쪽 배열의 남은 요소를 최종 배열에 복사.
	while (leftIndex < leftArrayLength)
	{
		array[mergedIndex] = leftArray[leftIndex];
		++leftIndex;
		++mergedIndex;
	}

	// 위의 과정에서 오른쪽 배열에 남은 요소를 최종 배열에 복사.
	while (rightIndex < rightArrayLength)
	{
		array[mergedIndex] = rightArray[rightIndex];
		++rightIndex;
		++mergedIndex;
	}
}

// Merge Sort (Recursion)
void MergeSort(int* array, int length)
{
	// Exit condition
	// Unable to divide.
	if (length <= 1)
	{
		return;
	}

	// Divide given array.
	int mid = length / 2;

	// Declare the devided array (create memory spaces)
	int* leftArray = new int[mid];
	int* rightArray = new int[length - mid];

	// memcpy: Copy array.
	memcpy(leftArray, array, sizeof(int) * mid);

	// Jump Pointer and memcpy.
	memcpy(rightArray, (array + mid), sizeof(int) * (length-mid));

	// Recursion: Merge Sort for Left Array
	MergeSort(leftArray, mid);

	
	// Recursion: Merge Sort for Right Array
	MergeSort(rightArray, (length - mid));

	// Merge.
	Merge(array, leftArray, mid, rightArray, (length - mid));

	// Delete the dynamic arrays.
	delete[] leftArray;
	delete[] rightArray;
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

	// Get the item count of the array.
	int length = _countof(array);

	MergeSort(array, length);

	PrintArray(array, length);

	return 0;
}