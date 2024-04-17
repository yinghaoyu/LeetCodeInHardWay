#include <algorithm>
#include <vector>

using namespace std;

// 分组背包
// @sa https://www.bilibili.com/video/BV1UM411f7YL/
class Solution
{
 public:
  // piles是一组一组的硬币
  // m是容量，表示一定要进行m次操作
  // dp[i][j] : 1~i组上，一共拿走j个硬币的情况下，获得的最大价值
  // 1) 不要i组的硬币 : dp[i-1][j]
  // 2) i组里尝试每一种方案
  // 比如，i组里拿走前k个硬币的方案 : dp[i-1][j-k] + 从顶部开始前k个硬币的价值和
  // 枚举每一个k，选出最大值
  int maxValueOfCoins1(vector<vector<int>>& piles, int m)
  {
    int n = piles.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
    {
      // i从1组开始（我们的设定），但是题目中的piles是从下标0开始的
      // 所以来到i的时候，piles[i-1]是当前组
      auto& team = piles[i - 1];
      int t = std::min(team.size(), (size_t) m);
      // 预处理前缀和，为了加速计算
      vector<int> preSum(t + 1);
      for (int j = 0, sum = 0; j < t; j++)
      {
        sum += team[j];
        preSum[j + 1] = sum;
      }
      // 更新动态规划表
      for (int j = 0; j <= m; j++)
      {
        // 当前组一个硬币也不拿的方案
        dp[i][j] = dp[i - 1][j];
        for (int k = 1; k <= std::min(t, j); k++)
        {
          dp[i][j] = std::max(dp[i][j], dp[i - 1][j - k] + preSum[k]);
        }
      }
    }
    return dp[n][m];
  }

  // 空间压缩
  int maxValueOfCoins2(vector<vector<int>>& piles, int m)
  {
    vector<int> dp(m + 1);
    for (auto& team : piles)
    {
      int t = std::min(team.size(), (size_t) m);
      // 预处理前缀和，为了加速计算
      vector<int> preSum(t + 1);
      for (int j = 0, sum = 0; j < t; j++)
      {
        sum += team[j];
        preSum[j + 1] = sum;
      }
      for (int j = m; j >= 0; j--)
      {
        for (int k = 1; k <= std::min(t, j); k++)
        {
          dp[j] = std::max(dp[j], dp[j - k] + preSum[k]);
        }
      }
    }
    return dp[m];
  }
};
