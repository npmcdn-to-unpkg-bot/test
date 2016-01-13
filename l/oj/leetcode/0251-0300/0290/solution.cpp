class Solution {
public:
    // beats 8.9% distribution 80%
    bool wordPattern(string pattern, string str) {
        if (!pattern.size() || !str.size()) {
            return false;
        }
        
        unordered_map<char, string> check;
        set<string> s;
        istringstream stream(str);
        string tmp, n;
        
        int i = 0;
        while(stream >> tmp) {
            const auto& c = pattern[i];
            const auto it = check.find(c);
            if (it != check.end()) {
                if (tmp != it->second) {
                    return false;
                }
            } else {
                if (s.find(tmp) != s.end()) {
                    return false;
                }
                check[c] = tmp;
                s.insert(tmp);
            }
            i++;
        }
        
        if (pattern.size() != i) {
            return false;
        }
        
        return true;
    }
}; 