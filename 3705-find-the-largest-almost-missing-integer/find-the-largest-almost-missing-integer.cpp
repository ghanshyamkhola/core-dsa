class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> count;

        // Check every subarray of size k
        for (int i = 0; i <= n - k; i++) {
            unordered_set<int> seen;

            for (int j = i; j < i + k; j++) {
                seen.insert(nums[j]);
            }

            // Each number is counted only once for this subarray
            for (int x : seen) {
                count[x]++;
            }
        }

        int ans = -1;

        // Find largest number appearing in exactly one subarray
        for (auto &[x, freq] : count) {
            if (freq == 1) {
                ans = max(ans, x);
            }
        }

        return ans;
    }
};