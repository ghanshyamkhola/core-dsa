class Solution {
public:
    int maxSelectedElements(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<int> dp(1000002, 0);
        int ans = 0;

        for (int x : nums) {
            int old = dp[x];

            // Use x as it is
            dp[x] = dp[x - 1] + 1;

            // Increase x -> x + 1
            dp[x + 1] = max(dp[x + 1], old + 1);

            ans = max(ans, max(dp[x], dp[x + 1]));
        }

        return ans;
    }
};