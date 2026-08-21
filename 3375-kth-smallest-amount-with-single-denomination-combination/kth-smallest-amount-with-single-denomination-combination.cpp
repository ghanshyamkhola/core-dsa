class Solution {
public:
    using ll = long long;

    ll gcdll(ll a, ll b) {
        return std::gcd(a, b);
    }

    ll lcmLimit(ll a, ll b, ll limit) {
        ll g = gcdll(a, b);

        // Prevent overflow
        if (a / g > limit / b)
            return limit + 1;

        return a / g * b;
    }

    ll countNumbers(ll x, vector<int>& coins) {
        int n = coins.size();
        ll ans = 0;

        for (int mask = 1; mask < (1 << n); mask++) {

            ll lcm = 1;
            int bits = 0;
            bool valid = true;

            for (int i = 0; i < n; i++) {

                if (mask & (1 << i)) {
                    bits++;

                    lcm = lcmLimit(lcm, coins[i], x);

                    if (lcm > x) {
                        valid = false;
                        break;
                    }
                }
            }

            if (!valid)
                continue;

            ll cnt = x / lcm;

            if (bits % 2 == 1)
                ans += cnt;
            else
                ans -= cnt;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {

        ll low = 1;

        ll high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {

            ll mid = low + (high - low) / 2;

            if (countNumbers(mid, coins) >= k)
                high = mid;
            else
                low = mid + 1;
        }

        return low;
    }
};