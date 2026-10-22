class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size();

        // Case 1: Circular increasing order
        bool inc = true;
        bool dec = true;

        for (int i = 1; i < n; i++) {
            if (nums[i] != (nums[i - 1] + 1) % n)
                inc = false;

            if (nums[i] != (nums[i - 1] - 1 + n) % n)
                dec = false;
        }

        if (inc) {
            int p = (n - nums[0]) % n;
            return min(p, n - p + 2);
        }

        // Case 2: Circular decreasing order
        if (dec) {
            int k = (nums[0] + 1) % n;
            return 1 + min(k, (n - k) % n);
        }

        return -1;
    }
};