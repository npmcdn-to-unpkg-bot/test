/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
	// 14% and best.
    vector<int> inorderTraversal(TreeNode* root) {
        if (!root) {
            return vector<int>();
        }
        vector<int> res;
        inorderTraversal(root, res);
        return res;
    }
    
    void inorderTraversal(TreeNode* root, vector<int>& result) {
        if (!root) {
            return;
        }
        inorderTraversal(root->left, result);
        result.push_back(root->val);
        inorderTraversal(root->right, result);
    }
}; 