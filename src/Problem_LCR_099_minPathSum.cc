#include <stdint.h>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/minimum-path-sum/
// @sa Problem_0064_minPathSum.cc
class Solution
{
 public:
  int minPathSum(vector<vector<int>>& grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, INT32_MAX));
    dp[n - 1][m - 1] = grid[n - 1][m - 1];
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = m - 1; j >= 0; j--)
      {
        int distance = std::min(dp[i + 1][j], dp[i][j + 1]);
        if (distance != INT32_MAX)
        {
          dp[i][j] = distance + grid[i][j];
        }
      }
    }
    return dp[0][0];
  }
};
