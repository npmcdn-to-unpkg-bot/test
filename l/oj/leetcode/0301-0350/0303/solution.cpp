 class NumArray {
public:
    // 56%
    NumArray(vector<int> &nums): v(nums.size(), 0) {
        if (nums.empty()) {
            return;
        }
        v[0] = nums[0];
        for (int i=1; i<nums.size(); i++) {
            v[i] = v[i-1] + nums[i];
        }
    }

    int sumRange(int i, int j) {
        if (i < 0 || j <0 ||v.size() < i || v.size() < j){
            return 0;
        }
        int s = 0;
        return v[j] - v[i-1];
    }
private:
    vector<int> v;
};


// Your NumArray object will be instantiated and called as such:
// NumArray numArray(nums);
// numArray.sumRange(0, 1);
// numArray.sumRange(1, 2);