
class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2,
                               int k1, int k2) {
        long long k = 1LL * k1 + k2;
        int n = nums1.size();
        vector<int> diff(n);

        int mx = 0;
        long long sum = 0;

        for (int i = 0; i < n; i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
            sum += diff[i];
        }

        if (sum <= k) return 0;

        int lo = 0, hi = mx;

        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid) need += d - mid;
            }

            if (need <= k)
                hi = mid;
            else
                lo = mid + 1;
        }

        long long ans = 0;
        long long used = 0;

        for (int d : diff) {
            if (d > lo) {
                used += d - lo;
                d = lo;
            }
            ans += 1LL * d * d;
        }

        long long remaining = k - used;

        for (int i = 0; i < n && remaining > 0; i++) {
            if (diff[i] >= lo && lo > 0) {
                ans -= 2LL * lo - 1;
                remaining--;
            }
        }

        return ans;
    }
};
