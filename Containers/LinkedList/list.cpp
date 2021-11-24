#include "list.h"
#include <algorithm>

template <typename T>
List<T>::List()
{
	init();
}

template <typename T>
List<T>::~List()
{
	clear();
	delete nil;
}

template <typename T>
List<T>::List(const List& rhs)
{
	init();
	for (const auto& x : rhs)
		push_back(x);
}

template <typename T>
List<T>::List(List&& rhs)
	: m_size{ rhs.m_size }, nil{ rhs.nil }
{
	rhs.m_size = 0;
	rhs.nil = nullptr;
}

template <typename T>
List<T>& List<T>::operator= (const List<T>& rhs)
{
	List copy{ rhs };
	std::swap(*this, copy);

	return *this;
}

template <typename T>
List<T>& List<T>::operator= (List<T>&& rhs) noexcept
{
	if (this == &rhs)
		return *this;

	clear();
	delete nil;

	nil = rhs.nil;
	m_size = rhs.m_size;
	rhs.nil = nullptr;
	rhs.m_size = 0;

	return *this;
}

template <typename T>
void List<T>::init()
{
	m_size = 0;
	nil = new Node{};
	nil->prev = nil;
	nil->next = nil;
}

template <typename T>
typename List<T>::iterator List<T>::insert(
	typename List<T>::iterator pos, const T& x)
{
	Node* p{ pos.current };
	++m_size;
	return { p->prev = p->prev->next = new Node{x, p, p->prev} };
}

template <typename T>
typename List<T>::iterator List<T>::insert(
	typename List<T>::iterator pos, T&& x)
{
	Node* p{ pos.current };
	++m_size;
	return { p->prev = p->prev->next = new Node{std::move(x), p, p->prev} };
}

template <typename T>
typename List<T>::iterator List<T>::erase(
	typename List<T>::iterator pos)
{
	Node* p{ pos.current };
	iterator retVal{ { p->next } };
	p->next->prev = p->prev;
	p->prev->next = p->next;

	delete p;
	--m_size;

	return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::erase(
	typename List<T>::iterator from, typename List<T>::iterator to)
{
	for (auto itr{ from }; itr != to;)
		itr = erase(itr);

	return to;
}