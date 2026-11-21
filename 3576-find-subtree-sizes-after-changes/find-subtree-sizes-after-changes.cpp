class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        // newParent[i] = parent of i after all simultaneous changes
        vector<int> newParent = parent;

        // last[c] = closest node with character c on current DFS path
        vector<int> last(26, -1);

        // Build original children
        vector<vector<int>> children(n);
        for (int i = 1; i < n; i++) {
            children[parent[i]].push_back(i);
        }

        // Find new parent for every node
        function<void(int)> dfs = [&](int u) {
            int c = s[u] - 'a';

            int old = last[c];

            // old is the closest ancestor with same character
            if (old != -1) {
                newParent[u] = old;
            }

            // Put current node on the path
            last[c] = u;

            for (int v : children[u]) {
                dfs(v);
            }

            // Restore previous node when backtracking
            last[c] = old;
        };

        dfs(0);

        // Build final tree
        vector<vector<int>> finalChildren(n);

        for (int i = 1; i < n; i++) {
            finalChildren[newParent[i]].push_back(i);
        }

        // Calculate subtree sizes
        vector<int> ans(n, 1);

        function<void(int)> calc = [&](int u) {
            for (int v : finalChildren[u]) {
                calc(v);
                ans[u] += ans[v];
            }
        };

        calc(0);

        return ans;
    }
};