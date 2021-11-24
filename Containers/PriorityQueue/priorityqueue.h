#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <vector>
#include <functional>
#include <utility>
#include <algorithm>
#include <cassert>
#include <iostream>

template <
	typename T,
	typename Container = std::vector<T>,
	typename Compare = std::less<typename Container::value_type>
> class PriorityQueue
{
public:
	PriorityQueue() : PriorityQueue(Compare(), Container()) {}
	PriorityQueue(const Compare& cmp) : PriorityQueue(cmp, Container()) {}
	PriorityQueue(const Compare& cmp, const Container& cont)
		: comp(cmp), c(cont) {
		buildHeap();
	};
	PriorityQueue(const Compare& cmp, Container&& cont)
		: comp(cmp), c(std::move(cont)) {
		buildHeap();
	};
	PriorityQueue(const PriorityQueue& other)
		: comp(other.comp), c(other.c) {}
	PriorityQueue(PriorityQueue&& other)
		: comp(other.comp), c(std::move(other.c)) {}

	PriorityQueue& operator= (const PriorityQueue& other)
	{
		comp = other.comp;
		c = other.c;

		return *this;
	}
	PriorityQueue& operator= (PriorityQueue&& other)
	{
		comp = other.comp;
		c = std::move(other.c);

		other.c = Container();

		return *this;
	}

	const T& top() const
	{
		assert(!empty() && "top() called on empty queue");
		return c.front();
	}
	bool empty() const	{ return size() == 0; }
	int size() const	{ return static_cast<int>(c.size()); }

	void push(const T& value)
	{
		c.push_back(value);
		insert();
	}
	void push(T&& value)
	{
		c.push_back(std::move(value));
		insert();
	}
	template<typename... Args>
	void emplace(Args&&... args)
	{
		c.emplace_back(std::forward<Args>(args)...);
		insert();
	}
	void pop()				{ extractTop(); }

private:
	Compare comp;
	Container c;

	int parent(int index)	{ return ((index + 1) >> 1) - 1; }
	int left(int index)		{ return (index << 1) + 1; }
	int right(int index)	{ return (index << 1) + 2; }

	void heapify(int i)
	{
		int l{};
		int r{};
		int top{};

		while (true)
		{
			l = left(i);
			r = right(i);

			if (l < size() && comp(c[i], c[l]))
				top = l;
			else
				top = i;
			if (r < size() && comp(c[top], c[r]))
				top = r;

			if (i == top)
				return;

			std::swap(c[i], c[top]);
			i = top;
		}
	}
	void buildHeap()
	{
		for (int i{ size() / 2 - 1 }; i >= 0; --i)
			heapify(i);
	}
	T extractTop()
	{
		assert(size() > 0 && "heap underflow");

		T topElement{ top() };
		c[0] = c[size() - 1];
		c.pop_back();
		heapify(0);

		return topElement;
	}
	void insert()
	{
		int i{ size() - 1 };
		while (i > 0 && comp(c[parent(i)], c[i]))
		{
			std::swap(c[parent(i)], c[i]);
			i = parent(i);
		}
	}
};

#endif // !BINARYHEAP_H