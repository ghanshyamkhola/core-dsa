
class Solution {
public:
    int minInsertions(string s) {
        int ans = 0;
        int open = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } 
            else {
                // If the next character is ')',
                // use it as the second closing bracket.
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } 
                else {
                    // Insert one ')' to make '))'
                    ans++;
                }

                // Match the closing pair with an opening '('
                if (open > 0) {
                    open--;
                } 
                else {
                    // Insert '(' to match this closing pair
                    ans++;
                }
            }
        }

        // Each remaining '(' needs two ')'
        ans += open * 2;

        return ans;
    }
};