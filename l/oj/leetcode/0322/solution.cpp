class Solution {
public:
	// 37.88%, a bad one
	// O(N*M) time, O(M) space
    int coinChange(vector<int>& coins, int amount) {
        if (amount < 0) {
            return -1;
        }

        // amount can be 0.
        vector<int> dp(amount + 1, -1); // cache result
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (const auto& coin : coins) {
                if (coin > i) {
                    continue;
                }
                if (coin == i) {
                    dp[i] = 1;
                } else {
                    int n = dp[i - coin];
                    if (n != -1) {
                        dp[i] = dp[i] == -1 ? n + 1 : min(dp[i], n+1);
                    }
                }
            }
        }
        return dp[amount];
    }
}; 