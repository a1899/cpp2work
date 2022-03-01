#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>

template <typename T>
class BSTree
{
private:
	struct Node;
public:
	BSTree() = default;
	~BSTree();
	BSTree(const BSTree& other);
	BSTree(BSTree&& other) noexcept;
	BSTree& operator= (const BSTree& other);
	BSTree& operator= (BSTree&& other) noexcept;

	const Node* minimum() const		{ return minimum(root); }
	const Node* maximum() const		{ return maximum(root); };
	const Node* predecessor(const T& value) const;
	const Node* successor(const T& value) const;

	int size() const			{ return m_size; }
	bool empty() const			{ return size() == 0; }
	const Node* search(const T& value) const;
	void inorderTreeWalk() const	{ inorderTreeWalk(root); }

	Node* insert(const T& value);
	Node* insert(T&& value);
	void erase(const T& value);
	void clear() { clear(root); };

private:
	Node* root{ nullptr };
	int m_size{ 0 };

	Node* insert(Node* t);
	Node* clone(Node* t, Node* parent);
	Node* search(const T& value);
	Node* minimum(Node* t) const;
	Node* maximum(Node* t) const;
	void clear(Node*& t);
	void transplant(Node* u, Node* v);
	void inorderTreeWalk(const Node* node) const;
};

template <typename T>
struct BSTree<T>::Node
{
	T data;
	Node* left;
	Node* right;
	Node* p;

	Node(const T& d = T(), Node* pr = nullptr, Node* l = nullptr, Node* r = nullptr)
		: data{ d }, p{ pr }, left{ l }, right{ r }
	{
	}
	Node(T&& d, Node* pr = nullptr, Node* l = nullptr, Node* r = nullptr)
		: data{ std::move(d) }, p{ pr }, left{ l }, right{ r }
	{
	}
};

#endif // !BSTREE_H
