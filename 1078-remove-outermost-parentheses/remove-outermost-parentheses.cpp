class Solution {
public:
    string removeOuterParentheses(string s) {
        string ans;
        int depth = 0;

        for (char ch : s) {
            if (ch == '(') {
                // Skip the outermost '('
                if (depth > 0) {
                    ans += ch;
                }
                depth++;
            } 
            else {
                depth--;

                // Skip the outermost ')'
                if (depth > 0) {
                    ans += ch;
                }
            }
        }

        return ans;
    }
};