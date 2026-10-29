class Solution {
public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        vector<vector<int>> adj(n);

        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<int> parent(n, -1), depth(n, 0);
        vector<int> sz(n, 1), heavy(n, -1);
        vector<int> head(n), pos(n);
        vector<int> order;
        order.reserve(n);

        // Iterative traversal: calculate parent and depth.
        vector<int> st = {0};
        parent[0] = 0;

        while (!st.empty()) {
            int u = st.back();
            st.pop_back();
            order.push_back(u);

            for (int v : adj[u]) {
                if (v == parent[u]) continue;

                parent[v] = u;
                depth[v] = depth[u] + 1;
                st.push_back(v);
            }
        }

        // Calculate subtree sizes and heavy children.
        for (int i = n - 1; i >= 0; --i) {
            int u = order[i];
            int maxSize = 0;

            for (int v : adj[u]) {
                if (parent[v] != u) continue;

                sz[u] += sz[v];

                if (sz[v] > maxSize) {
                    maxSize = sz[v];
                    heavy[u] = v;
                }
            }
        }

        // Assign HLD positions.
        int timer = 0;
        vector<pair<int, int>> chains = {{0, 0}};

        while (!chains.empty()) {
            auto [start, h] = chains.back();
            chains.pop_back();

            for (int u = start; u != -1; u = heavy[u]) {
                head[u] = h;
                pos[u] = timer++;

                for (int v : adj[u]) {
                    if (parent[v] == u && v != heavy[u]) {
                        chains.push_back({v, v});
                    }
                }
            }
        }

        // Segment tree storing character parity masks.
        int base = 1;
        while (base < n) base <<= 1;

        vector<int> seg(2 * base, 0);

        for (int u = 0; u < n; ++u) {
            seg[base + pos[u]] = 1 << (s[u] - 'a');
        }

        for (int i = base - 1; i > 0; --i) {
            seg[i] = seg[i << 1] ^ seg[i << 1 | 1];
        }

        auto update = [&](int p, int val) {
            p += base;
            seg[p] = val;

            for (p >>= 1; p > 0; p >>= 1) {
                seg[p] = seg[p << 1] ^ seg[p << 1 | 1];
            }
        };

        auto rangeQuery = [&](int l, int r) {
            int res = 0;

            l += base;
            r += base;

            while (l <= r) {
                if (l & 1) res ^= seg[l++];
                if (!(r & 1)) res ^= seg[r--];

                l >>= 1;
                r >>= 1;
            }

            return res;
        };

        auto pathQuery = [&](int u, int v) {
            int mask = 0;

            while (head[u] != head[v]) {
                if (depth[head[u]] < depth[head[v]]) {
                    swap(u, v);
                }

                mask ^= rangeQuery(pos[head[u]], pos[u]);
                u = parent[head[u]];
            }

            if (depth[u] > depth[v]) swap(u, v);

            mask ^= rangeQuery(pos[u], pos[v]);

            return mask;
        };

        vector<bool> ans;

        for (const string& q : queries) {
            stringstream ss(q);
            string op;
            int u, v;

            ss >> op >> u;

            if (op == "update") {
                char c;
                ss >> c;

                s[u] = c;
                update(pos[u], 1 << (c - 'a'));
            } else {
                ss >> v;

                int mask = pathQuery(u, v);

                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};