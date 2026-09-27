class Solution {
public:
    string reverseParentheses(string s) {
        stack<string> st;
        string curr = "";

        for (char ch : s) {

            if (ch == '(') {
                // Save the string before this '('
                st.push(curr);
                curr = "";
            }
            else if (ch == ')') {
                // Reverse the current substring
                reverse(curr.begin(), curr.end());

                // Add it to the previous level
                curr = st.top() + curr;
                st.pop();
            }
            else {
                // Normal character
                curr += ch;
            }
        }

        return curr;
    }
};