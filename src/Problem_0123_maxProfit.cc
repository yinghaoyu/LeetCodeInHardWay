#include <algorithm>
#include <clocale>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 动态规划
  int maxProfit1(vector<int>& prices)
  {
    int n = prices.size();
    // dp[i][j][k] 含义是：
    // 到第i天，进行了j次买入，k是否持有股票
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(3, vector<int>(2)));
    // dp[0][1][0] 含义是第0天，买入1次股票，然后当天就卖出去1次，因此收益为0
    dp[0][1][0] = 0;
    // dp[0][1][0] 含义是第0天，买入1次股票，持有，因此收益为 -prices[0]
    dp[0][1][1] = -prices[0];
    // dp[0][2][0] 含义是第0天，买入2次股票，然后当天就卖出去2次，因此收益为0
    dp[0][2][0] = 0;
    // dp[0][2][0] 含义是第0天，买入2次股票，然后当天就卖出去1次，因此收益为-prices[0]
    dp[0][2][1] = -prices[0];
    for (int i = 1; i < n; i++)
    {
      dp[i][1][0] = std::max(dp[i - 1][1][0], dp[i - 1][1][1] + prices[i]);
      dp[i][1][1] = std::max(dp[i - 1][1][1], dp[i - 1][0][0] - prices[i]);
      dp[i][2][0] = std::max(dp[i - 1][2][0], dp[i - 1][2][1] + prices[i]);
      dp[i][2][1] = std::max(dp[i - 1][2][1], dp[i - 1][1][0] - prices[i]);
    }
    return dp[n - 1][2][0];
  }

  // 贪心
  int maxProfit2(vector<int>& prices)
  {
    if (prices.size() == 0)
    {
      return 0;
    }
    int ans = 0;
    // doneOnceMinusBuyMax含义：
    // 在购买1次股票能获得的最大收益的前提下 减去 购买第2次股票的钱
    int doneOnceMinusBuyMax = -prices[0];
    // doneOnceMax 含义为购买1次股票能获得的最大收益
    int doneOnceMax = 0;  // 0 : [0] - [0]
    int min = prices[0];
    for (int i = 1; i < prices.size(); i++)
    {
      ans = std::max(ans, doneOnceMinusBuyMax + prices[i]);
      min = std::min(min, prices[i]);
      doneOnceMax = std::max(doneOnceMax, prices[i] - min);
      doneOnceMinusBuyMax = std::max(doneOnceMinusBuyMax, doneOnceMax - prices[i]);
    }
    return ans;
  }
};

void testMaxProfit()
{
  Solution s;
  vector<int> p1 = {3, 3, 5, 0, 0, 3, 1, 4};
  vector<int> p2 = {7, 6, 4, 3, 1};
  vector<int> p3 = {1, 2, 3, 4, 5};
  EXPECT_EQ_INT(6, s.maxProfit1(p1));
  EXPECT_EQ_INT(0, s.maxProfit1(p2));
  EXPECT_EQ_INT(4, s.maxProfit1(p3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxProfit();
  return 0;
}
