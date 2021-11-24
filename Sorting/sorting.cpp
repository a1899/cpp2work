#include "sorting.h"
#include <algorithm>
#include <functional>
#include <queue>
#include <limits>
#include <random>
#include <ctime>
#include <vector>
#include <utility>
#include <cmath>

template <class T>
void selectionSort(T* arr, int size)
{
	int minIndex{};
	for (int i = 0; i < size - 1; ++i)
	{
		minIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[minIndex])
				minIndex = j;
		}
		std::swap(arr[i], arr[minIndex]);;
	}
}

template <class T>
void bubbleSort(T* arr, int size)
{
	bool swapped{ true };
	while (swapped)
	{
		swapped = false;
		for (int i = 0; i < size - 1; ++i)
		{
			if (arr[i] > arr[i + 1])
			{
				swap(arr + i, arr + i + 1);
				swapped = true;
			}
		}
		--size;
	}
}

template <class T>
void insertionSort(T* arr, int size)
{
	for (int i = 1; i < size; ++i)
	{
		int key = arr[i];
		int j = i - 1;

		while (j >= 0 && key < arr[j])
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = key;
	}
}

template <class T>
void heapSort(T* arr, int size)
{
	std::priority_queue<T> queue(std::less<T>{}, std::vector<T>(size));
	for (int i = 0; i < size; ++i)
		queue.push(arr[i]);

	for (int i = 0; i < size; ++i)
	{
		arr[i] = queue.top();
		queue.pop();
	}
}

template<typename T>
void MergeSort<T>::merge(T* data, int p, int q, int r)
{
	int lSize{ q - p + 1 };
	int rSize{ r - q };
	auto left{ new T[lSize + 1] };
	auto right{ new  T[rSize + 1] };

	for (int index{ 0 }; index < lSize; ++index)
		left[index] = data[p + index];
	for (int index{ 0 }; index < rSize; ++index)
		right[index] = data[q + 1 + index];

	left[lSize] = std::numeric_limits<int>::max();
	right[rSize] = std::numeric_limits<int>::max();

	int lIndex{ 0 };
	int rIndex{ 0 };

	for (int index{ p }; index <= r; ++index)
	{
		if (right[rIndex] < left[lIndex])
		{
			data[index] = right[rIndex];
			++rIndex;
		}
		else
		{
			data[index] = left[lIndex];
			++lIndex;
		}
	}
	delete[] left;
	delete[] right;
}

template<typename T>
void MergeSort<T>::sort(T* data, int p, int r)
{
	if (p < r)
	{
		int q{ p + (r - p) / 2 };
		sort(data, p, q);
		sort(data, q + 1, r);
		merge(data, p, q, r);
	}
}

template<typename T>
int QuickSort<T>::getRandomNumber(int min, int max)
{
	static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
	return std::uniform_int_distribution{ min, max }(mt);
}

template<typename T>
int QuickSort<T>::randomizedPartition(T* data, int p, int r)
{
	int rIndex{ getRandomNumber(p, r) };
	std::swap(data[rIndex], data[r]);
	return partition(data, p, r);
}

template<typename T>
int QuickSort<T>::partition(T* data, int p, int r)
{
	T pivot{ data[r] };
	int i{ p - 1 };
	int j{ p - 1 };

	for (int k{ p }; k < r; ++k)
	{
		if (data[k] < pivot)
		{
			std::swap(data[++i], data[k]);
			++j;

			if (data[k] == pivot)
				std::swap(data[j], data[k]);
		}
		else if (data[k] == pivot)
		{
			std::swap(data[++j], data[k]);
		}
	}
	std::swap(data[j + 1], data[r]);
	return i + (j - i) / 2 + 1;
}

template<typename T>
void QuickSort<T>::sort(T* data, int p, int r)
{
	if (p < r)
	{
		int q{ randomizedPartition(data, p, r) };
		sort(data, p, q - 1);
		sort(data, q + 1, r);
	}
}

int RadixSort::digit(int number, int digitPosition)
{
	return (number / static_cast<int>(
		std::pow(radix, digitPosition)
		)) % radix;
}

void RadixSort::countingSort(const int* in, int* out, int size, int pos)
{
	int* count{ new int[radix] {} };

	for (int i{ 0 }; i < size; ++i)
		++count[digit(in[i], pos)];

	for (int i{ 1 }; i < radix; ++i)
		count[i] += count[i - 1];

	for (int i{ (size - 1) }; i >= 0; --i)
		out[--count[digit(in[i], pos)]] = in[i];

	delete[] count;
}

void RadixSort::sort(int* arr, int size, int higestOrderDigit)
{
	int* buffer{ new int[size] {} };

	int** in{ &arr };
	int** out{ &buffer };

	for (int pos{ 0 }; pos < higestOrderDigit; ++pos)
	{
		countingSort(*in, *out, size, pos);
		std::swap(in, out);
	}

	if (higestOrderDigit % 2 != 0)
	{
		for (int i{ 0 }; i < size; ++i)
			(*out)[i] = (*in)[i];
	}

	delete[] buffer;
}

template class MergeSort<int>;
template class QuickSort<int>;