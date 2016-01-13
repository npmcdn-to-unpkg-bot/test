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
	// 19.75% because 80% has the same runtime as mine
	// So this is the best answer i think.
    vector<int> rightSideView(TreeNode* root) {
        vector<int> result;
        rightSideView(root, 0, result);
        return result;
    }
    
    void rightSideView(TreeNode* root, int level, vector<int>& res) {
        if (!root) {
            return;
        }
        // Only the first one push in
        if (res.size() == level) {
            res.push_back(root->val);
        }
        // Right first
        rightSideView(root->right, level + 1, res);
        rightSideView(root->left, level + 1, res);
    }
};