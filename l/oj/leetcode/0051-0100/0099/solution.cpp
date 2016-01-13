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
    // 69%
    // If we do in-order traversal O(logn) space can get the two wrong elements which
    // is not permitted.
    //  1 2 3 4 5 6 7 8 inorder sort, two cases.
    //  1 2 (4) (3) 5 6 7 8
    //  first pre > now, s1 = pre, s2 = root
    //  1 2 (7) 4 5 6 (3) 9
    //  first pre > now, s1 = pre,
    //  second pre > now, s2 = root
    void recoverTree(TreeNode* root) {
        if (!root) {
            return;
        }
        TreeNode *s1, *s2, *pre;
        s1 = s2 = pre = nullptr;
        inorder_traversal(root, s1, s2, pre);
        swap(s1->val, s2->val);
    }
    
    void inorder_traversal(TreeNode* root, TreeNode*& s1, TreeNode*& s2, TreeNode*& pre) {
        if (!root) {
            return;
        }
        
        inorder_traversal(root->left, s1, s2, pre);
        
        if (pre && pre->val >= root->val) {
            if (!s1) {
                s1 = pre;
                s2 = root;
            } else {
                s2 = root;
            }
        }
        pre = root;
        
        inorder_traversal(root->right, s1, s2, pre);
    }
};