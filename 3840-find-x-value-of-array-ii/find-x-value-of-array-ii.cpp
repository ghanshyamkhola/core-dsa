class Solution {
public:
    static const int MAXK = 5;

    struct Node {
        int prod;
        long long pref[MAXK];
        long long suff[MAXK];
        long long cnt[MAXK];

        Node() {
            prod = 0;
            memset(pref, 0, sizeof(pref));
            memset(suff, 0, sizeof(suff));
            memset(cnt, 0, sizeof(cnt));
        }
    };

    int n, k;
    vector<Node> tree;

    // Empty / identity node
    Node identity() {
        Node res;
        res.prod = 1 % k;
        return res;
    }

    Node makeNode(int x) {
        Node res;

        int r = x % k;

        res.prod = r;

        // One prefix: the element itself
        res.pref[r] = 1;

        // One suffix: the element itself
        res.suff[r] = 1;

        // One subarray: the element itself
        res.cnt[r] = 1;

        return res;
    }

    Node mergeNode(const Node& a, const Node& b) {
        Node res;

        // Product of complete segment
        res.prod = (a.prod * b.prod) % k;

        // -------------------------
        // Prefix
        // -------------------------

        // Prefix lies completely in a
        for (int r = 0; r < k; r++) {
            res.pref[r] += a.pref[r];
        }

        // Prefix = whole a + prefix of b
        for (int r = 0; r < k; r++) {
            if (b.pref[r] == 0)
                continue;

            int newRem = (a.prod * r) % k;

            res.pref[newRem] += b.pref[r];
        }

        // -------------------------
        // Suffix
        // -------------------------

        // Suffix lies completely in b
        for (int r = 0; r < k; r++) {
            res.suff[r] += b.suff[r];
        }

        // Suffix = suffix of a + whole b
        for (int r = 0; r < k; r++) {
            if (a.suff[r] == 0)
                continue;

            int newRem = (r * b.prod) % k;

            res.suff[newRem] += a.suff[r];
        }

        // -------------------------
        // Subarrays
        // -------------------------

        // Completely inside a
        for (int r = 0; r < k; r++) {
            res.cnt[r] += a.cnt[r];
        }

        // Completely inside b
        for (int r = 0; r < k; r++) {
            res.cnt[r] += b.cnt[r];
        }

        // Crossing a -> b
        for (int i = 0; i < k; i++) {
            if (a.suff[i] == 0)
                continue;

            for (int j = 0; j < k; j++) {
                if (b.pref[j] == 0)
                    continue;

                int newRem = (i * j) % k;

                res.cnt[newRem] +=
                    a.suff[i] * b.pref[j];
            }
        }

        return res;
    }

    void build(vector<int>& nums) {
        for (int i = 0; i < n; i++) {
            tree[n + i] = makeNode(nums[i]);
        }

        for (int i = n - 1; i >= 1; i--) {
            tree[i] = mergeNode(
                tree[i << 1],
                tree[i << 1 | 1]
            );
        }
    }

    void update(int pos, int val) {
        pos += n;

        tree[pos] = makeNode(val);

        for (pos >>= 1; pos >= 1; pos >>= 1) {
            tree[pos] = mergeNode(
                tree[pos << 1],
                tree[pos << 1 | 1]
            );

            if (pos == 1)
                break;
        }
    }

    Node query(int l, int r) {
        Node left = identity();
        Node right = identity();

        l += n;
        r += n;

        while (l <= r) {

            if (l & 1) {
                left = mergeNode(left, tree[l]);
                l++;
            }

            if (!(r & 1)) {
                right = mergeNode(tree[r], right);
                r--;
            }

            l >>= 1;
            r >>= 1;
        }

        return mergeNode(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int K,
        vector<vector<int>>& queries
    ) {
        n = nums.size();
        k = K;

        tree.resize(2 * n);

        build(nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto& q : queries) {

            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(index, value);

            // Query nums[start ... n-1]
            Node res = query(start, n - 1);

            // Number of non-empty prefixes
            // having product % k == x
            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};