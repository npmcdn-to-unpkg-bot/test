class Solution {
public:
    // time limit exceeded
    int climbStairs(int n) {
        if (n <= 0) {
            return 0;
        }

        unordered_map<int, int> ways;
        return c(n, ways);
    }
    
    int c(int n, unordered_map<int,int>& ways) {
        const auto& it = ways.find(n);
        if (it != ways.end()) {
            return it->second;
        }

        if (n == 1) {
            ways[1] = 1;
            return 1;
        }
        if (n == 2) {
            ways[2] = 2;
            return 2;
        }
        
        return c(n-1, ways) + c(n-2, ways); 
    }
};

class Solution {
public:
    // beats 2.7% distribution 96%
    int climbStairs(int n) {
        if (n <= 0) {
            return 0;
        }
        if (n==1) {
            return 1;
        }
        if (n==2) {
            return 2;
        }

        int one_step_before = 2;
        int two_step_before = 1;
        int all = 0;
        for (int i=3; i<=n; i++) {
            all = one_step_before + two_step_before;
            two_step_before = one_step_before;
            one_step_before = all;
        }
        return all;
    }
};
