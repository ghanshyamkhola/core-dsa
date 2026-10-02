
class Solution {
public:
    void solve(int open, int close, int n, string curr, vector<string>& ans) {
        // If all parentheses are used
        if (curr.size() == 2 * n) {
            ans.push_back(curr);
            return;
        }

        // Add '(' if open parentheses are remaining
        if (open < n) {
            solve(open + 1, close, n, curr + '(', ans);
        }

        // Add ')' only when it won't make the string invalid
        if (close < open) {
            solve(open, close + 1, n, curr + ')', ans);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        solve(0, 0, n, "", ans);
        return ans;
    }
};