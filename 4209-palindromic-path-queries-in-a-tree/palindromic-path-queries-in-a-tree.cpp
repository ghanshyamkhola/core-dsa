class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges, string s, vector<string>& queries) {
        vector<vector<int>> adj(n);
        for (auto& e : edges) { adj[e[0]].push_back(e[1]); adj[e[1]].push_back(e[0]); }

        // iterative dfs: euler in/out times, parent, depth
        vector<int> tin(n), tout(n), par(n, -1), dep(n, 0), order;
        order.reserve(n);
        {
            vector<pair<int,int>> st = {{0, -1}};
            int timer = 0;
            while (!st.empty()) {
                auto [u, p] = st.back(); st.pop_back();
                if (p == -2) continue;
                tin[u] = timer++; order.push_back(u);
                par[u] = p; dep[u] = (p == -1) ? 0 : dep[p] + 1;
                st.push_back({u, -2});
                for (int v : adj[u]) if (v != p) st.push_back({v, u});
            }
        }
        vector<int> sub(n, 1);
        for (int i = n - 1; i >= 1; i--) sub[par[order[i]]] += sub[order[i]];
        for (int i = 0; i < n; i++) tout[i] = tin[i] + sub[i]; // exclusive end of subtree

        int LOG = 1; while ((1 << LOG) < n) LOG++;
        vector<vector<int>> up(LOG, vector<int>(n));
        for (int v = 0; v < n; v++) up[0][v] = (par[v] == -1) ? 0 : par[v];
        for (int k = 1; k < LOG; k++)
            for (int v = 0; v < n; v++) up[k][v] = up[k-1][up[k-1][v]];
        auto lca = [&](int u, int v) -> int {
            if (dep[u] < dep[v]) swap(u, v);
            int d = dep[u] - dep[v];
            for (int k = 0; k < LOG; k++) if (d >> k & 1) u = up[k][u];
            if (u == v) return u;
            for (int k = LOG - 1; k >= 0; k--)
                if (up[k][u] != up[k][v]) { u = up[k][u]; v = up[k][v]; }
            return par[u];
        };

        // 26 fenwicks over euler positions 1..n
        // +1 at tin, -1 at tout: prefix(tin[u]) = char counts on root->u path
        vector<array<int,26>> f(n + 1);
        auto add = [&](int c, int i, int d) {
            for (; i <= n; i += i & -i) f[i-1][c] += d;
        };
        auto ask = [&](int c, int i) -> int {
            int r = 0;
            for (; i > 0; i -= i & -i) r += f[i-1][c];
            return r;
        };
        for (int i = 0; i < n; i++) {
            int c = s[i] - 'a';
            add(c, tin[i] + 1, 1);
            if (tout[i] < n) add(c, tout[i] + 1, -1); // write at n+1 would be unread, skip it
        }
        auto cnt = [&](int c, int u) { return ask(c, tin[u] + 1); };

        vector<bool> ans;
        for (auto& q : queries) {
            if (q[0] == 'u') {
                int u = 0, i = 7;
                while (q[i] != ' ') u = u * 10 + (q[i++] - '0');
                char c = q.back();
                add(s[u] - 'a', tin[u] + 1, -1);
                if (tout[u] < n) add(s[u] - 'a', tout[u] + 1, 1);
                s[u] = c;
                add(c - 'a', tin[u] + 1, 1);
                if (tout[u] < n) add(c - 'a', tout[u] + 1, -1);
            } else {
                int u = 0, v = 0, i = 6;
                while (q[i] != ' ') u = u * 10 + (q[i++] - '0');
                i++;
                while (i < (int)q.size()) v = v * 10 + (q[i++] - '0');
                int w = lca(u, v);
                int odd = 0;
                for (int c = 0; c < 26 && odd <= 1; c++) {
                    int k = cnt(c, u) + cnt(c, v) - 2 * cnt(c, w) + (s[w] - 'a' == c);
                    if (k & 1) odd++;
                }
                ans.push_back(odd <= 1);
            }
        }
        return ans;
    }
};
