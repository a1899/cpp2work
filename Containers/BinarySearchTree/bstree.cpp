#include "bstree.h"
#include <algorithm>
#include <utility>

template <typename T>
BSTree<T>::~BSTree()
{
	clear(root);
}

template <typename T>
void BSTree<T>::clear(Node*& t)
{
	if (t != nullptr)
	{
		clear(t->left);
		clear(t->right);
		delete t;
		--m_size;
	}

	t = nullptr;
}

template <typename T>
BSTree<T>::BSTree(const BSTree& other) : m_size{ other.m_size }
{
	root = clone(other.root, nullptr);
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::clone(Node* t, Node* parent)
{
	if (t == nullptr)
		return nullptr;

	Node* temp{ new Node {t->data, parent} };
	temp->left = clone(t->left, temp);
	temp->right = clone(t->right, temp);
	return temp;
}

template <typename T>
BSTree<T>::BSTree(BSTree&& other) noexcept
	: root{ other.root }, m_size{ other.m_size }
{
	other.root = nullptr;
	other.m_size = 0;
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(const BSTree<T>& other)
{
	BSTree copy{ other };
	std::swap(*this, copy);

	return *this;
}

template <typename T>
BSTree<T>& BSTree<T>::operator=(BSTree<T>&& other) noexcept
{
	if (this == &other)
		return *this;

	clear(root);
	root = other.root;
	m_size = other.m_size;
	other.root = nullptr;
	other.m_size = 0;

	return *this;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::minimum(typename BSTree<T>::Node* t) const
{
	while (t->left != nullptr)
		t = t->left;

	return t;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::maximum(typename BSTree<T>::Node* t) const
{
	while (t->right != nullptr)
		t = t->right;

	return t;
}

template <typename T>
const typename BSTree<T>::Node* BSTree<T>::predecessor(const T& value) const
{
	const Node* x{ search(value) };
	if (x == nullptr)
		return nullptr;

	if (x->left != nullptr)
		return maximum(x->left);

	Node* y{ x->p };
	while (y != nullptr && x == y->left)
	{
		x = y;
		y = y->p;
	}

	return y;
}

template <typename T>
const typename BSTree<T>::Node* BSTree<T>::successor(const T& value) const
{
	const Node* x{ search(value) };
	if (x == nullptr)
		return nullptr;

	if (x->right != nullptr)
		return minimum(x->right);

	Node* y{ x->p };
	while (y != nullptr && x == y->right)
	{
		x = y;
		y = y->p;
	}

	return y;
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::search(const T& value)
{
	Node* x{ root };

	while (x != nullptr && value != x->data)
	{
		if (value < x->data)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template <typename T>
const typename BSTree<T>::Node* BSTree<T>::search(const T& value) const
{
	Node* x{ root };

	while (x != nullptr && value != x->data)
	{
		if (value < x->data)
			x = x->left;
		else
			x = x->right;
	}

	return x;
}

template <typename T>
void BSTree<T>::inorderTreeWalk(const typename BSTree<T>::Node* node) const
{
	if (node != nullptr)
	{
		inorderTreeWalk(node->left);
		std::cout << node->data << ' ';
		inorderTreeWalk(node->right);
	}
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::insert(const T& value)
{
	Node* temp{ new Node {value} };
	++m_size;
	return insert(temp);
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::insert(T&& value)
{
	Node* temp{ new Node {std::move(value)} };
	++m_size;
	return insert(temp);
}

template <typename T>
typename BSTree<T>::Node* BSTree<T>::insert(typename BSTree<T>::Node* t)
{
	Node* y{ nullptr };
	Node* x{ root };

	while (x != nullptr)
	{
		y = x;
		if (t->data < x->data)
			x = x->left;
		else
			x = x->right;
	}

	t->p = y;

	if (y == nullptr)
		root = t;
	else if (t->data < y->data)
		y->left = t;
	else
		y->right = t;


	return t;
}

template <typename T>
void BSTree<T>::erase(const T& value)
{
	Node* x{ search(value) };
	if (x == nullptr)
		return;

	if (x->left == nullptr)
		transplant(x, x->right);
	else if (x->right == nullptr)
		transplant(x, x->left);
	else
	{
		Node* y{ minimum(x->right) };
		if (y->p != x)
		{
			transplant(y, y->right);
			y->right = x->right;
			x->right->p = y;
		}
		transplant(x, y);
		y->left = x->left;
		y->left->p = y;
	}
	--m_size;
	delete x;
}

template <typename T>
void BSTree<T>::transplant(typename BSTree<T>::Node* u, typename BSTree<T>::Node* v)
{
	if (u->p == nullptr)
		root = v;
	else if (u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;

	if (v != nullptr)
		v->p = u->p;
}