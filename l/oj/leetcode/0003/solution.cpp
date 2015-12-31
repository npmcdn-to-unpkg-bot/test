class Solution {

public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0) {
            return 0;
        }

        vector<int> char_map(256, -1);
        int d = 0;
        int head = 0;
        for (int i = 0; i < s.size(); i++) {
            if (char_map[s[i]] != -1) {
                head = max(char_map[s[i]] + 1, head);
            }
            char_map[s[i]] = i;
            d = max(i - head + 1, d);
        }
        return d;
    }
};
