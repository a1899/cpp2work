#ifndef LIST_H
#define LIST_H

#include <utility>

template <typename T>
class List
{
private:
	struct Node;
public:
	class const_iterator;
	class iterator;
public:
	List();
	~List();
	List(const List& rhs);
	List(List&& rhs);
	List& operator= (const List& rhs);
	List& operator= (List&& rhs) noexcept;

	const_iterator begin() const { return { nil->next }; }
	iterator begin() { return { nil->next }; }
	const_iterator end() const { return { nil }; }
	iterator end() { return { nil }; }

	int size() const { return m_size; }
	bool empty() const { return m_size == 0; }

	void clear()
	{
		while (!empty())
			pop_front();
	}

	const T& front() const { return *begin(); }
	T& front() { return *begin(); }
	const T& back() const { return *--end(); }
	T& back() { return *--end(); }

	void push_back(const T& x) { insert(end(), x); }
	void push_back(T&& x) { insert(end(), std::move(x)); }
	void push_front(const T& x) { insert(begin(), x); }
	void push_front(T&& x) { insert(begin(), std::move(x)); }
	void pop_back() { erase(--end()); }
	void pop_front() { erase(begin()); }

	iterator insert(iterator pos, const T& x);
	iterator insert(iterator pos, T&& x);
	iterator erase(iterator pos);
	iterator erase(iterator from, iterator to);

	template<typename... Args>
	iterator emplace(iterator pos, Args&&... args)
	{
		Node* p{ pos.current };
		++m_size;
		return { p->prev = p->prev->next = new Node{
			T(std::forward<Args>(args)...), p, p->prev
		} };
	}

private:
	Node* nil{};
	int m_size{};

	void init();
};

template <typename T>
struct List<T>::Node
{
	T data;
	Node* next{};
	Node* prev{};

	Node(const T& d = T(), Node* n = nullptr, Node* p = nullptr)
		: data{ d }, next{ n }, prev{ p }
	{
	}
	Node(T&& d, Node* n = nullptr, Node* p = nullptr)
		: data{ std::move(d) }, next{ n }, prev{ p }
	{
	}
};

template <typename T>
class List<T>::const_iterator
{
public:
	const_iterator() = default;
	const T& operator* () const
	{
		return retrieve();
	}
	const_iterator& operator++ ()
	{
		current = current->next;
		return *this;
	}
	const_iterator operator++ (int)
	{
		const_iterator old{ *this };
		++(*this);

		return old;
	}
	const_iterator& operator-- ()
	{
		current = current->prev;
		return *this;
	}
	const_iterator operator-- (int)
	{
		const_iterator old{ *this };
		--(*this);

		return old;
	}
	bool operator== (const_iterator rhs) const
	{
		return current == rhs.current;
	}
	bool operator!= (const_iterator rhs) const
	{
		return !(*this == rhs);
	}

protected:
	Node* current;
	T& retrieve() const
	{
		return current->data;
	}
	const_iterator(Node* c) : current{ c }
	{
	}
	friend class List<T>;
};

template <typename T>
class List<T>::iterator : public List<T>::const_iterator
{
public:
	iterator() = default;
	const T& operator* () const
	{
		return const_iterator::operator*();
	}
	T& operator* ()
	{
		return const_iterator::retrieve();
	}
	iterator& operator++ ()
	{
		this->current = this->current->next;
		return *this;
	}
	iterator operator++ (int)
	{
		iterator old{ *this };
		++(*this);

		return old;
	}
	iterator& operator-- ()
	{
		this->current = this->current->prev;
		return *this;
	}
	iterator operator-- (int)
	{
		iterator old{ *this };
		--(*this);

		return old;
	}
protected:
	iterator(Node* c) : const_iterator{ c }
	{
	}
	friend class List<T>;
};

#endif // !LIST_H