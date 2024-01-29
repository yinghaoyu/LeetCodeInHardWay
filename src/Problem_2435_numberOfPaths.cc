#include <vector>

using namespace std;

class Solution
{
 private:
  static const int mod = 1e9 + 7;

 public:
  int numberOfPaths1(vector<vector<int>>& grid, int k)
  {
    int n = grid.size();
    int m = grid[0].size();
    return f1(grid, n, m, k, 0, 0, 0);
  }

  // 当前来到(i,j)位置，最终一定要走到右下角(n-1,m-1)
  // 从(i,j)出发，最终一定要走到右下角(n-1,m-1)，有多少条路径，累加和%k的余数是r
  int f1(vector<vector<int>>& grid, int n, int m, int k, int i, int j, int r)
  {
    if (i == n - 1 && j == m - 1)
    {
      return grid[i][j] % k == r ? 1 : 0;
    }
    // 后续需要凑出来的余数need
    int need = (k + r - (grid[i][j] % k)) % k;
    int ans = 0;
    if (i + 1 < n)
    {
      ans = f1(grid, n, m, k, i + 1, j, need);
    }
    if (j + 1 < m)
    {
      ans = (ans + f1(grid, n, m, k, i, j + 1, need)) % mod;
    }
    return ans;
  }

  int numberOfPaths2(vector<vector<int>>& grid, int k)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k, -1)));
    return f2(grid, n, m, k, 0, 0, 0, dp);
  }

  int f2(vector<vector<int>>& grid,
         int n,
         int m,
         int k,
         int i,
         int j,
         int r,
         vector<vector<vector<int>>>& dp)
  {
    if (i == n - 1 && j == m - 1)
    {
      return grid[i][j] % k == r ? 1 : 0;
    }
    if (dp[i][j][r] != -1)
    {
      return dp[i][j][r];
    }
    int need = (k + r - grid[i][j] % k) % k;
    int ans = 0;
    if (i + 1 < n)
    {
      ans = f2(grid, n, m, k, i + 1, j, need, dp);
    }
    if (j + 1 < m)
    {
      ans = (ans + f2(grid, n, m, k, i, j + 1, need, dp)) % mod;
    }
    dp[i][j][r] = ans;
    return ans;
  }

  // 空间优化
  int numberOfPaths3(vector<vector<int>>& grid, int k)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(m, vector<int>(k)));
    dp[n - 1][m - 1][grid[n - 1][m - 1] % k] = 1;
    for (int i = n - 2; i >= 0; i--)
    {
      for (int r = 0; r < k; r++)
      {
        dp[i][m - 1][r] = dp[i + 1][m - 1][(k + r - grid[i][m - 1] % k) % k];
      }
    }
    for (int j = m - 2; j >= 0; j--)
    {
      for (int r = 0; r < k; r++)
      {
        dp[n - 1][j][r] = dp[n - 1][j + 1][(k + r - grid[n - 1][j] % k) % k];
      }
    }
    for (int i = n - 2, need; i >= 0; i--)
    {
      for (int j = m - 2; j >= 0; j--)
      {
        for (int r = 0; r < k; r++)
        {
          need = (k + r - grid[i][j] % k) % k;
          dp[i][j][r] = dp[i + 1][j][need];
          dp[i][j][r] = (dp[i][j][r] + dp[i][j + 1][need]) % mod;
        }
      }
    }
    return dp[0][0][0];
  }
};
