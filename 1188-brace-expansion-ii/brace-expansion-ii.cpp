class Solution {
public:
    using Set = set<string>;

    // Parse one complete expression until '}' or end
    Set parse(string &s, int &i) {
        Set result;
        Set current = {""};

        while (i < s.size() && s[i] != '}') {

            if (s[i] == ',') {
                // Union
                for (auto &word : current)
                    result.insert(word);

                current = {""};
                i++;
            }
            else if (s[i] == '{') {
                i++; // skip '{'

                Set inside = parse(s, i);

                i++; // skip '}'

                // Concatenate current with inside
                Set temp;

                for (auto &a : current) {
                    for (auto &b : inside) {
                        temp.insert(a + b);
                    }
                }

                current = temp;
            }
            else {
                // Single lowercase letter
                string ch(1, s[i]);
                i++;

                Set temp;

                for (auto &word : current) {
                    temp.insert(word + ch);
                }

                current = temp;
            }
        }

        // Add the final part
        for (auto &word : current)
            result.insert(word);

        return result;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        Set ans = parse(expression, i);

        return vector<string>(ans.begin(), ans.end());
    }
};