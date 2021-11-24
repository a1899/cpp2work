#include "sorting.h"
#include <iostream>

int main()
{
	int arr[]{ 49, 231, 74, 537, 84 };
	RadixSort::sort(arr, 5, 3);
	for (int i{ 0 }; i < 5; ++i)
		std::cout << arr[i] << ' ';

	return 0;
}