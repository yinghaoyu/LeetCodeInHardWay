#include <climits>
#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/maximum-difference-score-in-a-grid/solutions/2877233/ju-zhen-zhong-de-zui-da-de-fen-by-leetco-c5tv/
class Solution
{
 public:
  int maxScore1(vector<vector<int>>& grid)
  {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> row(m, vector<int>(n));
    vector<vector<int>> col(m, vector<int>(n));
    vector<vector<int>> dp(m, vector<int>(n, INT_MIN));
    int ans = INT_MIN;
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i > 0)
        {
          dp[i][j] = std::max(dp[i][j], grid[i][j] + col[i - 1][j]);
        }
        if (j > 0)
        {
          dp[i][j] = std::max(dp[i][j], grid[i][j] + row[i][j - 1]);
        }
        ans = std::max(ans, dp[i][j]);
        row[i][j] = col[i][j] = std::max(dp[i][j], 0) - grid[i][j];
        if (i > 0)
        {
          col[i][j] = std::max(col[i][j], col[i - 1][j]);
        }
        if (j > 0)
        {
          row[i][j] = std::max(row[i][j], row[i][j - 1]);
        }
      }
    }
    return ans;
  }

  int maxScore2(vector<vector<int>>& grid)
  {
    int m = grid.size();
    int n = grid[0].size();
    int ans = INT_MIN;
    vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        int pre = INT_MAX;
        if (i > 0)
        {
          pre = std::min(pre, dp[i - 1][j]);
        }
        if (j > 0)
        {
          pre = std::min(pre, dp[i][j - 1]);
        }
        if (i + j > 0)
        {
          ans = std::max(ans, grid[i][j] - pre);
        }
        dp[i][j] = std::min(pre, grid[i][j]);
      }
    }
    return ans;
  }
};
