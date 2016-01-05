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
    // But this increase O(n) spaces
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

class Solution3 {
public:
    // 84.51%
    // Copy a new vector, O(N) space, because we use sort() for to sort.
    // Sort, O(NlogN)
    // Find elements O(N)
    // find index O(N)
    // So:  O(NlogN) time + O(N) space

    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result(2, 0);
        if (nums.size() < 2) {
            return result;
        }

        // O(NlogN)
        // sort will change the roginal vector, so sort a new one
        vector<int> numbers = nums;
        sort(numbers.begin(), numbers.end());

        // Find two elements O(N)
        int left = 0, right = numbers.size() - 1;
        vector<int> res;
        while (left < right) {
            int sum = numbers[left] + numbers[right];
            if (sum == target) {
                res.push_back(numbers[left]);
                res.push_back(numbers[right]);
                break;
            }
            if (sum < target) {
                left++;
            } else {
                right--;
            }
        }
        if (res.size() == 0) {
            return result;
        }
        cout << "element0:" << res[0] << ", element1:" << res[1] << endl;

        // Find the index O(N)
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == res[0] && result[0] == 0) {
                result[0] = i + 1;
            } else if (nums[i] == res[1] && result[1] == 0) {
                result[1] = i + 1;
            }
        }

        if (result[0] > result[1]) {
            swap(result[0], result[1]);
        }
        return result;
    }
};