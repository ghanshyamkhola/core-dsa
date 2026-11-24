class Solution {
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int ans = 1;

        // primes possible because nums[i] <= 10
        vector<int> primes = {2, 3, 5, 7};

        for (int i = 0; i < n; i++) {

            // sum[p]  = sum of exponents of prime p
            // mn[p]   = minimum exponent
            // mx[p]   = maximum exponent
            // cnt[p]  = how many numbers contain p
            int sum[4] = {};
            int mn[4] = {INT_MAX, INT_MAX, INT_MAX, INT_MAX};
            int mx[4] = {};
            int cnt[4] = {};

            for (int j = i; j < n; j++) {

                int x = nums[j];

                for (int p = 0; p < 4; p++) {

                    int exponent = 0;

                    while (x % primes[p] == 0) {
                        exponent++;
                        x /= primes[p];
                    }

                    sum[p] += exponent;
                    mx[p] = max(mx[p], exponent);
                    cnt[p]++;

                    // If prime didn't occur in current number,
                    // its exponent is 0.
                    mn[p] = min(mn[p], exponent);
                }

                bool valid = true;

                for (int p = 0; p < 4; p++) {
                    if (sum[p] != mn[p] + mx[p]) {
                        valid = false;
                        break;
                    }
                }

                if (valid) {
                    ans = max(ans, j - i + 1);
                }
            }
        }

        return ans;
    }
};