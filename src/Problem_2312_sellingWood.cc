#include <vector>

using namespace std;

class Solution
{
 public:
  // https://leetcode.cn/problems/selling-pieces-of-wood/solutions/1611240/by-endlesscheng-mrmd/
  long long sellingWood(int m, int n, vector<vector<int>>& prices)
  {
    vector<vector<int>> map(m + 1, vector<int>(n + 1));
    for (auto& p : prices)
    {
      // map[i][j] 表示高 i 宽 j 的木块直接卖掉的收益
      map[p[0]][p[1]] = p[2];
    }
    // dp[i][j] 表示切割一块高 i 宽 j 的木块，能得到的最多钱数
    vector<vector<long long>> dp(m + 1, vector<long long>(n + 1));

    for (int i = 1; i <= m; i++)
    {
      for (int j = 1; j <= n; j++)
      {
        dp[i][j] = map[i][j];
        // 可以优化为 k <= j / 2
        for (int k = 1; k <= j /* k<=j/2 */; k++)
        {
          // 垂直切割
          dp[i][j] = std::max(dp[i][j], dp[i][k] + dp[i][j - k]);
        }
        for (int k = 1; k <= i /* k<=i/2 */; k++)
        {
          // 水平切割
          dp[i][j] = std::max(dp[i][j], dp[k][j] + dp[i - k][j]);
        }
      }
    }
    return dp[m][n];
  }
};
