class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats for each row using a bitmask.
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];

            // Only seats 2 to 9 matter.
            if (col >= 2 && col <= 9) {
                mp[row] |= (1 << col);
            }
        }

        // Initially, every row can accommodate 2 groups.
        long long ans = 2LL * n;

        // Recalculate rows having reservations.
        for (auto &[row, mask] : mp) {
            
            // We initially counted 2 groups for this row.
            // Determine the actual number possible.

            bool left  = (mask & ((1 << 2) | (1 << 3) | 
                                 (1 << 4) | (1 << 5))) == 0;

            bool middle = (mask & ((1 << 4) | (1 << 5) | 
                                   (1 << 6) | (1 << 7))) == 0;

            bool right = (mask & ((1 << 6) | (1 << 7) | 
                                  (1 << 8) | (1 << 9))) == 0;

            int groups = 0;

            if (left) groups++;
            if (right) groups++;

            // If neither left nor right can be used,
            // middle may still accommodate one group.
            if (groups == 0 && middle)
                groups = 1;

            // Remove the previously assumed 2 groups
            // and add the actual number.
            ans -= 2;
            ans += groups;
        }

        return ans;
    }
};