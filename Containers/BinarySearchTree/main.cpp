#include "bstree.h"
#include <iostream>
#include <string>
#include <utility>

template <typename T>
void print(BSTree<T> t)
{
	std::cout << "size(): " << t.size() << " empty(): " << t.empty() << '\n';
	t.inorderTreeWalk();
	std::cout << "\n\n";
}

int main()
{
	BSTree<std::string> t1;
	t1.insert("abcd");
	std::string s{ "efg" };
	t1.insert(s);
	print(t1);

	BSTree<std::string> t2{ std::move(t1) };
	t2.insert("hijk");
	BSTree<std::string> t3;
	t3 = t2;
	t3.insert("lmnop");
	t3.insert("qrstuvw");
	t3.insert("xyz");
	print(t3);

	std::cout << "\"lmnop\" predecessor: " << t3.predecessor("lmnop")->data << '\n';
	std::cout << "\"lmnop\" successor: " << t3.successor("lmnop")->data << "\n\n";

	t3.erase("lmnop");
	print(t3);
	t3.clear();
	print(t3);

	return 0;
}