 class Solution {
public:
	// 43% and it's in the fastest distribution.
    string longestCommonPrefix(vector<string>& strs) {
        if (!strs.size()) {
            return "";
        }
        
        for (int i = 0; i < strs[0].size(); i++) {
            for (const auto& str : strs) {
                if (str[i] != strs[0][i]) {
                    return str.substr(0, i);
                }
            }
        }
        return strs[0];
    }
};