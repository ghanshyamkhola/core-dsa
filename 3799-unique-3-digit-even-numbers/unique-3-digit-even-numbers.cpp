class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int cnt[10] = {};

        // Count frequency of each digit
        for (int d : digits) {
            cnt[d]++;
        }

        int ans = 0;

        // Try every 3-digit number
        for (int num = 100; num <= 999; num++) {

            // Must be even
            if (num % 2 != 0)
                continue;

            int x = num;

            int a = x / 100;          // hundreds digit
            int b = (x / 10) % 10;    // tens digit
            int c = x % 10;           // ones digit

            // Check whether we have enough copies
            int need[10] = {};
            need[a]++;
            need[b]++;
            need[c]++;

            bool possible = true;

            for (int d = 0; d <= 9; d++) {
                if (need[d] > cnt[d]) {
                    possible = false;
                    break;
                }
            }

            if (possible)
                ans++;
        }

        return ans;
    }
};