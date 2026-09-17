class Solution {
public:
    int minSumOfLengths(vector<int>& arr, int target) {
        int n = arr.size();

        // best[i] = minimum length of a valid subarray
        // completely within arr[0...i]
        vector<int> best(n, INT_MAX);

        int ans = INT_MAX;
        int left = 0;
        long long sum = 0;

        for (int right = 0; right < n; right++) {
            sum += arr[right];

            // Shrink window if sum becomes greater than target
            while (sum > target) {
                sum -= arr[left];
                left++;
            }

            // Found a subarray [left ... right]
            if (sum == target) {
                int len = right - left + 1;

                // Previous non-overlapping subarray
                if (left > 0 && best[left - 1] != INT_MAX) {
                    ans = min(ans, len + best[left - 1]);
                }

                // Minimum valid subarray seen so far
                if (right == 0)
                    best[right] = len;
                else
                    best[right] = min(best[right - 1], len);
            }
            else {
                // No subarray ending at right, carry previous best
                if (right > 0)
                    best[right] = best[right - 1];
            }
        }

        return ans == INT_MAX ? -1 : ans;
    }
};