#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution {
    struct State {
        long long weight = 0;
        vector<int> indices;

        // Custom comparator to maximize weight, then minimize lexicographical order of indices
        bool isBetterThan(const State& other) const {
            if (weight != other.weight) {
                return weight > other.weight;
            }
            // If weights are equal, pick lexicographically smaller list of indices
            return indices < other.indices;
        }
    };

public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        
        // Store [l, r, weight, original_index]
        vector<vector<int>> sorted_intervals(n);
        for (int i = 0; i < n; ++i) {
            sorted_intervals[i] = {intervals[i][0], intervals[i][1], intervals[i][2], i};
        }
        
        // Sort intervals by right endpoint r
        sort(sorted_intervals.begin(), sorted_intervals.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // Extract right endpoints for binary search
        vector<int> rights(n);
        for (int i = 0; i < n; ++i) {
            rights[i] = sorted_intervals[i][1];
        }

        // dp[k][i] stores best State choosing at most k non-overlapping intervals from sorted_intervals[0...i-1]
        // Base case dp[k][0] is all 0 weight and empty indices.
        vector<vector<State>> dp(5, vector<State>(n + 1));

        for (int i = 1; i <= n; ++i) {
            int l = sorted_intervals[i - 1][0];
            int r = sorted_intervals[i - 1][1];
            long long w = sorted_intervals[i - 1][2];
            int orig_idx = sorted_intervals[i - 1][3];

            // Binary search: find largest index j < i-1 such that rights[j] < l
            // upper_bound for l - 1 gives first element > (l - 1), so iterator - 1 gives last element <= (l - 1)
            int prev_idx = lower_bound(rights.begin(), rights.end(), l) - rights.begin();

            for (int k = 1; k <= 4; ++k) {
                // Option 1: Skip current interval
                State best = dp[k][i - 1];

                // Option 2: Include current interval
                State take = dp[k - 1][prev_idx];
                take.weight += w;
                
                // Insert orig_idx in sorted order to maintain lexicographical ordering of index sequence
                auto pos = lower_bound(take.indices.begin(), take.indices.end(), orig_idx);
                take.indices.insert(pos, orig_idx);

                // Choose the state that maximizes weight (and breaks ties lexicographically)
                if (take.isBetterThan(best)) {
                    best = take;
                }

                dp[k][i] = best;
            }
        }

        return dp[4][n].indices;
    }
};