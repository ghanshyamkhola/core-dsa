class Solution {
public:
    static const int MOD = 1e9 + 7;

    int numberOfSets(int n, int k) {
        // dp[j] = number of ways to make j segments
        // using points processed so far, with no segment currently open.
        vector<long long> dp(k + 1, 0);
        vector<long long> open(k + 1, 0);

        dp[0] = 1;

        for (int i = 1; i < n; i++) {
            // Process in decreasing order so that the current
            // point is not used multiple times incorrectly.
            for (int j = k; j >= 1; j--) {

                // Start a new segment at point i-1
                open[j] = (open[j] + dp[j - 1]) % MOD;

                // Extend an already started segment to point i
                dp[j] = (dp[j] + open[j]) % MOD;
            }
        }

        return dp[k];
    }
};