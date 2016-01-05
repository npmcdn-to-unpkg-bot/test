class Solution {
public:
    // A bad one. runtime only beats 9.56% of cpp submisstions.
    // This is o(n^2)
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result(2,0);
        for (int i=0; i<nums.size(); i++) {
            for (int j=i+1; j<nums.size(); j++) {
                if (nums[i] + nums[j] == target) {
                    result[0] = i + 1;
                    result[1] = j + 1;
                    return result;
                }
            }
        }
        return result;
    }
};

class Solution2 {
public:
    // defeats 58.7%
    // This is a better one with O(n), assuming unodered_map.find() is constaint time.
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result(2, 0);
        unordered_map<int,int> checked;
        for (int i = 0; i < nums.size(); i++) {
            const auto& it = checked.find(target - nums[i]);
            if (it != checked.end()) {
                result[0] = it->second + 1;
                result[1] = i + 1;
                return result;
            }
            
            checked[nums[i]] = i;
        }
        return result;
    }
};