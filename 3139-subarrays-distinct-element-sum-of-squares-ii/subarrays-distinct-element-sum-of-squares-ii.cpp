
class Solution {
public:
    static const int MOD = 1e9 + 7;

    int sumCounts(vector<int>& nums) {
        int n = nums.size();

        vector<long long> sum(4 * n, 0);
        vector<long long> sq(4 * n, 0);
        vector<long long> lazy(4 * n, 0);

        auto push = [&](auto&& self, int node, int l, int r) -> void {
            if (lazy[node] == 0 || l == r) return;

            int mid = (l + r) / 2;
            int left = node * 2;
            int right = left + 1;
            long long v = lazy[node];

            auto apply = [&](int child, int len) {
                sq[child] = (sq[child] + 2 * v % MOD * sum[child] % MOD
                             + v * v % MOD * len % MOD) % MOD;
                sum[child] = (sum[child] + v * len) % MOD;
                lazy[child] = (lazy[child] + v) % MOD;
            };

            apply(left, mid - l + 1);
            apply(right, r - mid);

            lazy[node] = 0;
        };

        auto update = [&](auto&& self, int node, int l, int r,
                          int ql, int qr) -> void {
            if (ql > r || qr < l) return;

            if (ql <= l && r <= qr) {
                long long len = r - l + 1;
                sq[node] = (sq[node] + 2 * sum[node] + len) % MOD;
                sum[node] = (sum[node] + len) % MOD;
                lazy[node] = (lazy[node] + 1) % MOD;
                return;
            }

            push(push, node, l, r);

            int mid = (l + r) / 2;
            self(self, node * 2, l, mid, ql, qr);
            self(self, node * 2 + 1, mid + 1, r, ql, qr);

            sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
            sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
        };

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int i = 0; i < n; i++) {
            int left = last[nums[i]] + 1;

            // Increase distinct counts for subarrays ending at i.
            update(update, 1, 0, n - 1, left, i);

            // Sum of squared distinct counts of all subarrays
            // ending at i.
            ans = (ans + sq[1]) % MOD;

            last[nums[i]] = i;
        }

        return (int)ans;
    }
};
