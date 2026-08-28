
class Solution {
public:

    string makePalindrome(string &half, char middle) {
        string ans = half;

        if (middle != '#')
            ans += middle;

        string rev = half;
        reverse(rev.begin(), rev.end());

        ans += rev;

        return ans;
    }

    string lexPalindromicPermutation(string s, string target) {

        int n = s.size();

        // Count characters
        vector<int> cnt(26, 0);

        for (char c : s) {
            cnt[c - 'a']++;
        }

        // Check if a palindrome is possible
        int odd = 0;
        char middle = '#';

        for (int i = 0; i < 26; i++) {

            if (cnt[i] % 2 == 1) {
                odd++;
                middle = char('a' + i);
            }
        }

        // More than one odd frequency -> impossible
        if (odd > 1)
            return "";

        // Count characters needed for first half
        vector<int> halfCnt(26);

        for (int i = 0; i < 26; i++) {
            halfCnt[i] = cnt[i] / 2;
        }

        int halfLen = n / 2;

        string targetHalf = target.substr(0, halfLen);

        // ------------------------------------------
        // First, check if targetHalf itself is possible
        // ------------------------------------------

        vector<int> rem = halfCnt;

        bool possible = true;

        for (char c : targetHalf) {

            int x = c - 'a';

            if (rem[x] == 0) {
                possible = false;
                break;
            }

            rem[x]--;
        }

        // If we can construct targetHalf,
        // check whether the resulting palindrome
        // is already strictly greater than target.
        if (possible) {

            string half = targetHalf;

            string candidate = makePalindrome(half, middle);

            if (candidate > target)
                return candidate;
        }

        // ------------------------------------------
        // Find the smallest half greater than targetHalf
        // ------------------------------------------

        for (int pos = halfLen - 1; pos >= 0; pos--) {

            // Reset counts
            rem = halfCnt;

            string prefix;
            bool ok = true;

            // Keep prefix equal to target
            for (int i = 0; i < pos; i++) {

                int x = targetHalf[i] - 'a';

                if (rem[x] == 0) {
                    ok = false;
                    break;
                }

                prefix += targetHalf[i];
                rem[x]--;
            }

            if (!ok)
                continue;

            // Try the smallest character greater
            // than targetHalf[pos]
            int cur = targetHalf[pos] - 'a';

            for (int x = cur + 1; x < 26; x++) {

                if (rem[x] == 0)
                    continue;

                string half = prefix;

                // Increase current position
                half += char('a' + x);

                rem[x]--;

                // Put remaining characters in sorted order
                for (int c = 0; c < 26; c++) {

                    while (rem[c] > 0) {
                        half += char('a' + c);
                        rem[c]--;
                    }
                }

                // Construct palindrome
                return makePalindrome(half, middle);
            }
        }

        return "";
    }
};

