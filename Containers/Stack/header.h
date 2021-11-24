#ifndef HEADER_H
#define HEADER_H

#include <deque>
#include <utility>
#include <string>

template<
	typename T, 
	typename Container = std::deque<T>
> class Stack
{
public:
	Stack() : Stack(Container()) {}
	Stack(const Container& cont) : c{ cont } {}
	Stack(Container&& cont) : c{ std::move(cont) } {}
	Stack(const Stack& other) : c{ other.c } {}
	Stack(Stack&& other) : c{ std::move(c) } {}

	Stack& operator= (const Stack& other)
	{
		c = other.c;
		return *this;
	}
	Stack& operator= (Stack&& other)
	{
		c = std::move(other.c);
		return *this;
	}

	T& top()					{ return c.back(); }
	const T& top() const		{ return c.back(); }

	bool empty() const			{ return size() == 0; }
	int size() const			{ return std::static_cast<int>(c.size()); }

	void push(const T& value)	{ c.push_back(value); }
	void push(T&& value)		{ c.push_back(std::move(value)); }
	void pop()					{ c.pop_back(); }

	template <typename... Args>
	void emplace(Args&&... args)
	{
		c.emplace_back(std::forward<Args>(args)...);
	}

private:
	Container c;
};

int longestValidSubstring(const std::string& str);
int maxHistArea(int* arr, int size);

#endif // !HEADER_H