class Solution {
public:
	// 56.86%
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        sort(strs.begin(), strs.end());
        vector<vector<string>> res;
        unordered_map<string, int> map;
        
        for (const auto& str : strs) {
            string tmp(str);
            sort(tmp.begin(), tmp.end());
            const auto& it = map.find(tmp);
            if (it != map.end()) {
                res[it->second].push_back(str);
            } else {
                res.push_back(vector<string>(1, str));
                map.emplace(tmp, res.size() - 1);
            }
        }
        return res;
    }
}; 