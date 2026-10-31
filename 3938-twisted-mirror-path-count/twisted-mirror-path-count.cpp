class Solution {
    int m, n;
    vector<vector<int>> memoR, memoD, *g;

    // where does the robot end up if it tries to enter (r,c) moving
    // right (d=0) or down (d=1)? returns cell index, or -1 if invalid
    int land(int r, int c, int d) {
        if (r >= m || c >= n) return -1;
        if (r == m-1 && c == n-1) return r*n+c;
        if ((*g)[r][c] == 0) return r*n+c;   // normal cell: stop here
        if (d == 0) { // entered moving right -> turned down
            if (memoR[r][c] != -1) return memoR[r][c];
            return memoR[r][c] = land(r+1, c, 1);
        } else {      // entered moving down -> turned right
            if (memoD[r][c] != -1) return memoD[r][c];
            return memoD[r][c] = land(r, c+1, 0);
        }
    }
public:
    int uniquePaths(vector<vector<int>>& grid) {
        g = &grid;
        m = grid.size(); n = grid[0].size();
        memoR.assign(m, vector<int>(n, -1));
        memoD.assign(m, vector<int>(n, -1));
        vector<long long> ways(m*n, 0);
        ways[0] = 1;
        for (int r = 0; r < m; r++)
            for (int c = 0; c < n; c++) {
                if (grid[r][c] != 0 || ways[r*n+c] == 0) continue;
                if (r == m-1 && c == n-1) continue;
                long long w = ways[r*n+c];
                int R = land(r, c+1, 0), D = land(r+1, c, 1);
                if (R != -1) ways[R] = (ways[R] + w) % 1000000007;
                if (D != -1) ways[D] = (ways[D] + w) % 1000000007;
            }
        return (int)ways[m*n-1];
    }
};
