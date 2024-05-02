#include <vector>

#include "UnitTest.h"

using namespace std;

// @sa https://www.bilibili.com/video/BV1PN411j7aG/
class Solution
{
 public:
  int maxProfit1(int k, vector<int>& prices)
  {
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(k + 1, vector<int>(2)));
    for (int i = 1; i < k + 1; i++)
    {
      dp[0][i][1] = -prices[0];
    }
    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j < k + 1; j++)
      {
        dp[i][j][0] = std::max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
        dp[i][j][1] = std::max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
      }
    }
    return dp[n - 1][k][0];
  }

  int maxProfit2(int k, vector<int>& prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int n = prices.size();
    // 一个数组最大的上坡数是 n / 2
    // 比如 {1,2,1,2,1,2}，所以只要交易次数满足 >= 可能最大上坡数，就等于抓取所有上坡
    if (k >= n / 2)
    {
      // 根据 122 题的结论：
      // 如果数组元素个数为N，则最多执行N/2次交易就可以抓取所有的上升段的值
      return allTrans(prices);
    }
    // dp[i][j]表示[0...i]范围内交易j次获得的最大收益是多少
    vector<vector<int>> dp(n, vector<int>(k + 1));
    // 第一行的值表示数组[0..0]范围内，交易若干次的最大收益，显然，都是0
    // 第一列的值表示数组[0...i]范围内，交易0次获得的最大收益，显然，也都是0
    for (int i = 1; i < n; i++)
    {
      for (int j = 1; j < k + 1; j++)
      {
        // i位置不参与交易
        dp[i][j] = dp[i - 1][j];
        // i位置如果参与交易，那么i位置一定是最后一次的卖出时机
        // 枚举最后一次的买入时机
        for (int p = 0; p <= i; p++)
        {
          // 最后一次买入的时机在i位置
          // FIXME: 这里枚举可以优化
          dp[i][j] = std::max(dp[p][j - 1] + prices[i] - prices[p], dp[i][j]);
        }
      }
    }
    return dp[n - 1][k];
  }

  int allTrans(vector<int>& prices)
  {
    int ans = 0;
    for (int i = 1; i < prices.size(); i++)
    {
      ans += std::max(prices[i] - prices[i - 1], 0);
    }
    return ans;
  }

  // 枚举优化
  // https://www.cnblogs.com/greyzeng/p/16182420.html
  int maxProfit3(int k, vector<int>& prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int n = prices.size();
    if (k >= n / 2)
    {
      return allTrans(prices);
    }
    vector<vector<int>> dp(n, vector<int>(k + 1));
    int ans = 0;
    for (int j = 1; j <= k; j++)
    {
      int pre = dp[j][0];
      int best = pre - prices[0];
      for (int i = 1; i < n; i++)
      {
        pre = dp[j - 1][i];
        dp[j][i] = std::max(dp[j][i - 1], prices[i] + best);
        best = std::max(best, pre - prices[i]);
        ans = std::max(dp[j][i], ans);
      }
    }
    return ans;
  }
};

void testMaxProfit()
{
  Solution s;
  vector<int> p1 = {2, 4, 1};
  vector<int> p2 = {3, 2, 6, 5, 0, 3};
  EXPECT_EQ_INT(2, s.maxProfit1(2, p1));
  EXPECT_EQ_INT(7, s.maxProfit1(2, p2));
  EXPECT_EQ_INT(2, s.maxProfit2(2, p1));
  EXPECT_EQ_INT(7, s.maxProfit2(2, p2));
  EXPECT_EQ_INT(2, s.maxProfit3(2, p1));
  EXPECT_EQ_INT(7, s.maxProfit3(2, p2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProfit();
  return 0;
}
