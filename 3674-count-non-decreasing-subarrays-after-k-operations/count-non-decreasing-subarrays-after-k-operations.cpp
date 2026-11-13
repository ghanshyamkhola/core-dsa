class Solution {
public:
    long long countNonDecreasingSubarrays(vector<int>& nums, int k) {
        int n = nums.size();

        deque<int> dq;

        long long cost = 0;
        long long ans = 0;

        int j = n - 1;

        // Process from right to left
        for (int i = n - 1; i >= 0; i--) {

            // Merge all smaller plateaus into nums[i]
            while (!dq.empty() && nums[dq.back()] < nums[i]) {

                int l = dq.back();
                dq.pop_back();

                int r = dq.empty() ? j + 1 : dq.back();

                // Raise nums[l] ... nums[r-1]
                // from nums[l] to nums[i]
                cost += 1LL * (r - l) *
                        (nums[i] - nums[l]);
            }

            dq.push_back(i);

            // Window is too expensive
            while (cost > k) {

                // Remove nums[j]
                cost -= nums[dq.front()] - nums[j];

                // If j itself is represented by the front,
                // remove it from the deque.
                if (dq.front() == j) {
                    dq.pop_front();
                }

                j--;
            }

            // Every subarray [i ... x], i <= x <= j is valid
            ans += j - i + 1;
        }

        return ans;
    }
};