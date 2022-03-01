// Given a binary tree, determine if it is height-balanced.

#include <cmath>
#include <unordered_map>
#include <iostream>

struct Node {
	int data;
	Node* left = nullptr;
	Node* right = nullptr;
};

/*
int height(Node* root) {
	if(root == nullptr)
		return 0;
	return  1 + std::max(height(root->left), height(root->right));	
}
*/
/*
int height(Node* root) {
	if(root == nullptr)
		return 0;
	static std::unordered_map<Node*, int> temp;
	if(temp.contains(root))
		return temp[root];
	int h = 1 + std::max(height(root->left), height(root->right));
	return temp[root] = h;
}
*/
/*
bool isBalanced(Node* root) {
	if(root == nullptr)
		return true;

	int leftHeight = height(root->left);
	int rightHeight = height(root->right);

	return (std::abs(leftHeight - rightHeight) <= 1) && 
		isBalanced(root->left) && isBalanced(root->right);
}
*/

int height(Node* root) {
	if(root == nullptr)
		return 0;
	int lh = height(root->left);
	if(lh == -1)
		return -1;
	int rh = height(root->right);
	if(rh == -1)
		return -1;
	if(std::abs(lh - rh) <= 1)
		return 1 + std::max(lh, rh);
	else
		return -1;	
}

bool isBalanced(Node* root) {
	int h = height(root);
	return h != -1;
}

void deleteNodes(Node* root) {
	if (root == nullptr)
		return;
	deleteNodes(root->left);
	deleteNodes(root->right);
	delete root;
}

int main()
{
	Node* root{new Node};
	root->left = new Node;
	root->right = new Node;
	root->left->left = new Node;
	root->left->left->left = new Node;
	
	std::cout << "is balanced: " << isBalanced(root) << '\n';
	
	deleteNodes(root);
	return 0;
}
