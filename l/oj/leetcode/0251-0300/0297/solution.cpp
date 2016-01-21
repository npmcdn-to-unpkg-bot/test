 /**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // ONLY 1.32% a bad one.
    // preorder traversal.
    // It's bad because I use a lot of string operations.
    // see the good one that use iostringstream.

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "";
        }
        
        string res;
        serialize(root, res);
        cout << "result is [" << res << "]" << endl;
        return res;
    }
    
    void serialize(TreeNode* root, string& result) {
        if (!result.empty()) {
            result += string(" ");
        }
        if (!root) {
            result += "null";
            return;
        }
        
        result += to_string(root->val);
        serialize(root->left, result);
        serialize(root->right, result);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        cout << "input string [" << data << "]" << endl;
        if (data.empty()) {
            return nullptr;
        }
        
        istringstream stream(data);
        string tmp;
        list<string> l;
        while(stream >> tmp) {
            l.push_back(tmp);
        }

        if (l.empty()) {
            cout << "list is empty" << endl;
            return nullptr;
        }
        
        TreeNode* p = nullptr;
        deserialize(p, l);
        return p;
    }
    
    void deserialize(TreeNode*& root, list<string>& l) {
        if (l.empty()) {
            return;
        }
        
        auto value = l.front();
        cout << "handle value: " << value << endl;
        l.pop_front();
        if (value == "null") {
            return;
        }
        
        root = new TreeNode(atoi(value.c_str()));
        deserialize(root->left, l);
        deserialize(root->right, l);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));




/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    // 56% the same as above but with iostringstream.
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) {
            return "";
        }
        
        ostringstream stream;
        serialize(root, stream);
        cout << "result is [" << stream.str() << "]" << endl;
        return stream.str();
    }
    
    void serialize(TreeNode* root, ostringstream& out) {
        if (!root) {
            out << "null ";
            return;
        }
        
        out << root->val << ' ';
        serialize(root->left, out);
        serialize(root->right, out);
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        cout << "input string [" << data << "]" << endl;
        if (data.empty()) {
            return nullptr;
        }
        
        istringstream in(data);
        TreeNode* p = nullptr;
        deserialize(p, in);
        return p;
    }
    
    void deserialize(TreeNode*& root, istringstream& in) {
        string tmp;
        if (in >> tmp && tmp != "null") {
            root = new TreeNode(atoi(tmp.c_str()));
            deserialize(root->left, in);
            deserialize(root->right, in);
        }
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));