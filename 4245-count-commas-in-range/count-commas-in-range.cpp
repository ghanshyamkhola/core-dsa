class Solution {
public:
    int countCommas(int n) {
        long long total = 0;
        long long lower = 1;
        int L = 1;
        
        while (lower <= n) {
            long long upper = lower * 10 - 1;
            if (upper > n) upper = n;
            
            long long cnt = upper - lower + 1;
            int commas = (L - 1) / 3;
            
            total += cnt * commas;
            
            lower *= 10;
            L++;
        }
        
        return (int)total;
    }
};