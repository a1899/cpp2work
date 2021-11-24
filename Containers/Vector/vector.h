#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <utility>

template <class T>
class Vector
{
public:
	using const_iterator = const T*;
	using iterator = T*;
public:
	explicit Vector(int count = 0);
	Vector(std::initializer_list<T> list);
	Vector(const Vector& other);
	Vector(Vector&& other) noexcept;
	virtual ~Vector();

	Vector& operator= (const Vector& other);
	Vector& operator= (Vector&& other) noexcept;
	Vector& operator= (std::initializer_list<T> list);

	iterator begin()						{ return c; }
	const_iterator begin() const			{ return c; }
	iterator end()							{ return c + size(); }
	const_iterator end() const				{ return c + size(); }

	T& operator[] (int index)				{ return c[index]; }
	const T& operator[] (int index) const	{ return c[index]; }

	T& back ()								{ return *(end() - 1); }
	const T& back () const					{ return *(end() - 1); }

	bool empty() const noexcept				{ return begin() == end(); }
	int size() const noexcept				{ return m_size; }
	int capacity() const noexcept			{ return m_capacity; }
	void reserve(int new_cap);
	void shrink_to_fit();

	void clear() noexcept;
	void push_back(const T& value);
	void push_back(T&& value);

	template<class... Args>
	T& emplace_back(Args&&... args)
	{
		resize(m_size + 1);
		new(end() - 1) T(std::forward<Args>(args)...);
		return back();
	}

	void pop_back()	{ --m_size; }
	void resize(int count);

private:
	int m_size{};
	int m_capacity{};
	T* c{ nullptr };

	static const int SPARE_CAPACITY{ 16 };
	void reallocate(int new_size);
};

#endif // !VECTOR_H