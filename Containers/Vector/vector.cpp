#include "vector.h"
#include <utility>
#include <algorithm>

template <class T>
Vector<T>::Vector(int count)
	: m_size{ count > 0 ? count : 0 },
	m_capacity{ m_size + SPARE_CAPACITY },
	c{ new T[m_capacity]{} }
{
}

template <class T>
Vector<T>::Vector(std::initializer_list<T> list)
	: Vector(static_cast<int>(list.size()))
{
	int i{ 0 };
	for (const T& x : list)
		c[i++] = x;
}

template <class T>
Vector<T>::Vector(const Vector& other)
	:m_size{ other.m_size }, m_capacity{ other.m_capacity }
{
	c = new T[m_capacity]{};
	for (int i{ 0 }; i < size(); ++i)
		c[i] = other.c[i];
}

template <class T>
Vector<T>::Vector(Vector&& other) noexcept
  : m_size{ other.m_size }, m_capacity{ other.m_capacity }, c{ other.c }
{
	other.m_size = other.m_capacity = 0;
	other.c = nullptr;
}

template <class T>
Vector<T>::~Vector()
{
	delete[] c;
}

template <class T>
Vector<T>& Vector<T>::operator= (const Vector& other)
{
	Vector copy{ other };
	std::swap(*this, copy);
	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator= (Vector&& other) noexcept
{
	if (this == &other)
		return *this;

	delete[] c;

	m_size = other.m_size;
	m_capacity = other.m_capacity;
	c = other.c;
	other.m_size = other.m_capacity = 0;
	other.c = nullptr;

	return *this;
}

template <class T>
Vector<T>& Vector<T>::operator= (std::initializer_list<T> list)
{
	Vector other(list);
	std::swap(*this, other);
	return *this;
}

template <class T>
void Vector<T>::reallocate(int new_size)
{
	T* temp{ new T[new_size]{} };
	for (int i{ 0 }; i < size(); ++i)
		temp[i] = std::move(c[i]);

	delete[] c;
	c = temp;
}

template <class T>
void Vector<T>::reserve(int new_cap)
{
	if (new_cap > m_capacity)
	{
		m_capacity = new_cap;
		reallocate(new_cap);
	}
}

template <class T>
void Vector<T>::shrink_to_fit()
{
	if (size() != capacity())
	{
		m_capacity = m_size;
		reallocate(size());
	}
}

template <class T>
void Vector<T>::clear() noexcept
{
	delete[] c;
	c = new T[capacity()]{};
	m_size = 0;
}

template <class T>
void Vector<T>::push_back(const T& value)
{
	resize(size() + 1);
	back() = value;
}

template <class T>
void Vector<T>::push_back(T&& value)
{
	resize(size() + 1);
	back() = std::move(value);
}

template <class T>
void Vector<T>::resize(int count)
{
	if(count > capacity())
		reserve(count * 2);

	for (int i{ size() }; i < count; ++i)
		c[i] = T();
	m_size = count;
}