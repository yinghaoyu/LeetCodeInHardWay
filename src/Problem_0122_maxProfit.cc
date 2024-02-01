#include <clocale>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // index 当前是第几天
  // status 0不持有股票，1持有股票
  // profit 当前收益
  void f(vector<int>& prices, int index, int status, int profit, int& ans)
  {
    if (index == prices.size())
    {
      ans = std::max(ans, profit);
      return;
    }
    // 不买入也不卖出
    f(prices, index + 1, status, profit, ans);
    // 买入或者卖出
    if (status == 0)
    {
      f(prices, index + 1, 1, profit - prices[index], ans);
    }
    else
    {
      f(prices, index + 1, 0, profit + prices[index], ans);
    }
  }

  // 递归
  int maxProfit1(vector<int>& prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int ans = 0;
    f(prices, 0, 0, 0, ans);
    return ans;
  }

  // 递归改动态规划
  int maxProfit2(vector<int>& prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int n = prices.size();
    // dp[i][0]的含义为，第i天不持有股票的最大收益
    // dp[i][1]的含义为，第i天持有股票的最大收益
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = 0;
    dp[0][1] = -prices[0];
    for (int i = 1; i < n; i++)
    {
      // 由于当前行只依赖上一行，这里可以空间优化
      dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
      dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - prices[i]);
    }
    return dp[n - 1][0];
  }

  // 贪心
  int maxProfit3(vector<int>& prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int ans = 0;
    for (int i = 1; i < prices.size(); i++)
    {
      // 可以把股票曲线的所有上升段都抓取到，累加收益就是最大收益
      // 由本题可以简单得出一个结论：
      // 如果数组元素个数为N，则最多执行N/2次交易就可以抓取所有的上升段的值
      // 极端情况下，当前时刻买，下一个时刻卖，保持这样的交易一直到最后，执行的交易次数就是N/2
      ans += std::max(prices[i] - prices[i - 1], 0);
    }
    return ans;
  }
};

void testMaxProfit()
{
  Solution s;
  vector<int> p1 = {7, 1, 5, 3, 6, 4};
  vector<int> p2 = {1, 2, 3, 4, 5};
  vector<int> p3 = {7, 6, 4, 3, 1};
  EXPECT_EQ_INT(7, s.maxProfit1(p1));
  EXPECT_EQ_INT(4, s.maxProfit1(p2));
  EXPECT_EQ_INT(0, s.maxProfit1(p3));
  EXPECT_EQ_INT(7, s.maxProfit2(p1));
  EXPECT_EQ_INT(4, s.maxProfit2(p2));
  EXPECT_EQ_INT(0, s.maxProfit2(p3));
  EXPECT_EQ_INT(7, s.maxProfit3(p1));
  EXPECT_EQ_INT(4, s.maxProfit3(p2));
  EXPECT_EQ_INT(0, s.maxProfit3(p3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProfit();
  return 0;
}
