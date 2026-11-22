class Solution {
public:
    bool checkString(string s) {
        bool foundB = false;

        for (char c : s) {
            if (c == 'b') {
                foundB = true;
            } 
            else if (foundB) {
                // Found 'a' after a 'b'
                return false;
            }
        }

        return true;
    }
};