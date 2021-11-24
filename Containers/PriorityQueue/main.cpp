#include "priorityqueue.h"
#include <vector>
#include <iostream>
#include <functional>
#include <utility>

template<typename T>
void print(const PriorityQueue<T>& q)
{
	std::cout << "size: " << q.size();
	if (!q.empty())
	{
		std::cout << " top: " << q.top();
	}
	std::cout << " empty: " << q.empty() << '\n';
}

int main()
{
	std::vector<int> v{ 18,3,8,12,9,7,15,11 };
	PriorityQueue<int> q1(std::less<int>{}, v);
	print(q1);

	PriorityQueue<int> q2(q1);
	q2.pop();
	print(q2);

	PriorityQueue<int> q3(std::move(q1));
	print(q1);
	print(q3);

	PriorityQueue<int> q4;
	q4.push(4);
	q4.pop();
	print(q4);

	q4.emplace(3);
	q4.emplace(7);
	print(q4);

	return 0;
}