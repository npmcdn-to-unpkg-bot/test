#include <iostream>
#include <vector>

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

void insert(TreeNode*& root, int val);
// h is height of tree, which is logn
// generate O(nlogn) which is also O(nh)
TreeNode* generate_bst(const std::vector<int>& v) {
    TreeNode* root = nullptr;
    for (const auto& entry : v) {
        insert(root, entry);
    }
    return root;
}

// Insert is O(h) or O(logn)
void insert(TreeNode*& root, int val) {
    if (!root) {
        root = new TreeNode(val);
        return;
    }

    if (val < root->val) {
        if (root->left) {
            insert(root->left, val);
        } else {
            root->left = new TreeNode(val);
        }
    } else {
        if (root->right) {
            insert(root->right, val);
        } else {
            root->right = new TreeNode(val);
        }
    }
}

// searching O(h) or O(logn)
TreeNode* search(TreeNode* root, int val) {
    while (root) {
        if (val == root->val) {
            return root;
        }

        if (val < root->val) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return nullptr;
}

// delete
void delete_node(TreeNode*& root, int val) {
    if (!root) {
        return;
    }

    TreeNode* p = root;
    TreeNode* parent = nullptr;
    while (p) {
        if (val == p->val) {
            break;
        }
        parent = p;
        p = val < p->val ? p->left : p->right;
    }

    // found no element
    if (!p) {
        return;
    }

    // no leaves
    if (!p->left && !p->right) {
        if (parent) {
            auto& parent_leaf = val < parent->val ? parent->left : parent->right;
            parent_leaf = nullptr;
        } else {
            // it's the root!
            root = nullptr;
        }
        delete p;
        return;
    }

    // two leaves
    if (p->left && p->right) {
        // found its Successor
        auto succssor = p->right;
        auto succssor_parent = p;
        while (succssor) {
            if(!succssor->left) {
                break;
            }
            succssor_parent = succssor;
            succssor = succssor->left;
        }
        // exchange the value
        p->val = succssor->val;
        // succssor最多有1个子节点,那就是right
        // refrence
        auto& succssor_parent_leaf = succssor_parent == p ? succssor_parent->right : succssor_parent->left;
        succssor_parent_leaf = succssor->right ? succssor->right : nullptr;
        delete succssor;
        return;
    }

    // has one leaf
    auto leaf = p->left ? p->left : p->right;
    if (parent) {
        // refrence
        auto& parent_leaf = val < parent->val ? parent->left : parent->right;
        parent_leaf = leaf;
    } else {
        root = leaf;
    }
    delete p;
}

// O(n)
void print_inorder_traversal(TreeNode* root) {
    if (!root) {
        return;
    }

    print_inorder_traversal(root->left);
    std::cout << root->val << std::endl;
    print_inorder_traversal(root->right);
}

// 
void print_depth_traversal(TreeNode* root) {
    if (!root) {
        return;
    }
    std::vector<TreeNode*> v;
    v.push_back(root);
    while(v.size()) {
        std::vector<TreeNode*> tmp;
        for (const auto& entry : v) {
            std::cout << entry->val << " ";
            if (entry->left) {
                tmp.push_back(entry->left);
            }
            if (entry->right) {
                tmp.push_back(entry->right);
            }
        }
        std::cout << std::endl;
        v.swap(tmp);
    }
}

int main(int argc, char** argv) {
    //      6
    //    /   \
    //   2     7
    //  / \     \
    // 1   4     8
    //    / \
    //   3   5
    int v0[] = { 6, 2, 4, 1, 7, 8, 3, 5};
    std::vector<int> v(v0, v0 + sizeof(v0)/sizeof(int));

    TreeNode* root = generate_bst(v);
    // print_inorder_traversal(root);
    print_depth_traversal(root);

    std::cout << "11 in bst ? " << (search(root, 11) != nullptr ? "Yes" : "No") << std::endl;
    std::cout << "3  in bst ? " << (search(root, 3) != nullptr ? "Yes" : "No") << std::endl;

    std::cout << "remove 4 ...." << std::endl;
    delete_node(root, 4);
    print_depth_traversal(root);
    std::cout << "remove 6 ...." << std::endl;
    delete_node(root, 6);
    print_depth_traversal(root);
    std::cout << "remove 5 ...." << std::endl;
    delete_node(root, 5);
    print_depth_traversal(root);
    std::cout << "remove 8 ...." << std::endl;
    delete_node(root, 8);
    print_depth_traversal(root);
}