class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        // Every number >= 1,000 has at least 1 comma
        long long p = 1000;

        while (p <= n) {
            ans += n - p + 1;

            // Prevent overflow
            if (p > n / 1000)
                break;

            p *= 1000;
        }

        return ans;
    }
};