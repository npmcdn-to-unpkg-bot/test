#include <iostream>
#include <cmath> // pow
#include <random>
#include <functional> // bind
#include <memory>
#include <vector>
#include <queue>

/*
  g++ --std=c++11 *.cpp
*/

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};


TreeNode* generate_tree(unsigned depth = 3) {
	if (depth == 0) {
		return nullptr;
	}
	int max = pow(2, depth) - 1;
	
}

// recursive
void pre_order_traversal(TreeNode* root) {
	if (!root) {
		return;
	}
	std::cout << root->val << " ";
	pre_order_traversal(root->left);
	pre_order_traversal(root->right);
}

void in_order_traversal(TreeNode* root) {
	if (!root) {
		return;
	}
	in_order_traversal(root->left);
	std::cout << root->val << " ";
	in_order_traversal(root->right);
}

void post_order_traversal(TreeNode* root) {
	if (!root) {
		return;
	}

	post_order_traversal(root->left);
	post_order_traversal(root->right);
	std::cout << root->val << " ";
}

// 即每一层从左向右输出, this is not a recursive method
void depth_traversal(TreeNode* root) {
	if (!root) {
		return;
	}
	
	std::vector<TreeNode*> q;
	q.push_back(root);
	while (q.size()) {
		std::vector<TreeNode*> tmp;
		for (const auto& entry : q) {
			std::cout << entry->val << " ";
			if (entry->left) {
				tmp.push_back(entry->left);
			}
			if (entry->right) {
				tmp.push_back(entry->right);
			}
		}
		std::cout << std::endl;
		q.swap(tmp);
	}
}

// non-recursive


int main(int argc, char** argv) {
	// auto dice = std::bind(std::uniform_int_distribution<int>(1, 100), std::default_random_engine());
	/*
			1
		   / \
		  2   3
		 / \ / \
		4  5 6  7
	pre-order : 1 2 4 5 3 6 7
	in-order  : 4 2 5 1 6 3 7
	post-order: 4 5 2 6 7 3 1
	*/
	TreeNode* head = new TreeNode(1);
	head->left = new TreeNode(2);
	head->right = new TreeNode(3);
	head->left->left = new TreeNode(4);
	head->left->right = new TreeNode(5);
	head->right->left = new TreeNode(6);
	head->right->right = new TreeNode(7);

	pre_order_traversal(head);
	std::cout << std::endl;
	in_order_traversal(head);
	std::cout << std::endl;
	post_order_traversal(head);
	std::cout << std::endl;
	depth_traversal(head);
}