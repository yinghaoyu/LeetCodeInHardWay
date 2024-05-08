#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 动态规划
  int cherryPickup(vector<vector<int>>& grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(m + 1, vector<int>(m + 1)));
    for (int x = n - 1; x >= 0; x--)
    {
      for (int y1 = 0; y1 < m; y1++)
      {
        for (int y2 = m - 1; y2 >= 0; y2--)
        {
          for (int i = y1 - 1; i <= y1 + 1; i++)
          {
            for (int j = y2 - 1; j <= y2 + 1; j++)
            {
              if (i < 0 || i >= m || j < 0 || j >= m)
              {
                continue;
              }
              if (y1 == y2)
              {
                // 同一处樱桃只能摘 1 次
                dp[x][y1][y2] = std::max(dp[x][y1][y2], dp[x + 1][i][j] + grid[x][y1]);
              }
              else
              {
                dp[x][y1][y2] =
                    std::max(dp[x][y1][y2], dp[x + 1][i][j] + grid[x][y1] + grid[x][y2]);
              }
            }
          }
        }
      }
    }
    return dp[0][0][m - 1];
  }
};
