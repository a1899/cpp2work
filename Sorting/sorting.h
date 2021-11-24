#ifndef SORTING_H
#define SORTING_H

template <class T>
void selectionSort(T* arr, int size);

template <class T>
void bubbleSort(T* arr, int size);

template <class T>
void insertionSort(T* arr, int size);

template <class T>
void heapSort(T* arr, int size);

template<typename T>
class MergeSort
{
public:
	static void sort(T* data, int p, int r);
private:
	static void merge(T* data, int p, int q, int r);
};

template<typename T>
class QuickSort
{
public:
	static void sort(T* data, int p, int r);
private:
	static int getRandomNumber(int min, int max);
	static int randomizedPartition(T* data, int p, int r);
	static int partition(T* data, int p, int r);
};

class RadixSort
{
public:
	static void sort(int* arr, int size, int higestOrderDigit);
private:
	static void countingSort(const int* in, int* out, int size, int pos);
	static int digit(int number, int digitPosition);
	static constexpr int radix{ 10 };
};

#endif // !SORTING_H
