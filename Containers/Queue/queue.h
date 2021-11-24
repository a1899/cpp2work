#ifndef QUEUE_H
#define QUEUE_H

#include <deque>
#include <utility>

template <
	typename T,
	typename Container = std::deque<T>
> class Queue
{
public:
	Queue() : Queue(Container()) {}
	Queue(const Container& cont) : c{ cont } {}
	Queue(Container&& cont) : c{ std::move(cont) } {}
	Queue(const Queue& other) : c{ other.c } {}
	Queue(Queue&& other) : c{ std::move(other.c) } {}

	Queue& operator= (const Queue& other)
	{
		c = other.c;
		return *this;
	}
	Queue& operator= (Queue&& other)
	{
		c = std::move(other.c);
		return *this;
	}

	T& front()					{ return c.front(); }
	const T& front() const		{ return c.back(); }
	T& back()					{ return c.front(); }
	const T& back() const		{ return c.back(); }

	bool empty() const			{ return size() == 0; }
	int size() const			{ return static_cast<int>(c.size()); }

	void push(const T& value)	{ c.push_back(value); }
	void push(T&& value)		{ c.push_back(std::move(value)); }
	void pop()					{ c.pop_front(); }

	template <typename... Args>
	void emplace(Args&&... args)
	{
		c.emplace_back(std::forward<Args>(args)...);
	}

private:
	Container c;
};

#endif // !QUEUE_H