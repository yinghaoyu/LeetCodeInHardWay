#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  long long maxTaxiEarnings(int n, vector<vector<int>>& rides)
  {
    vector<long long> dp(n + 1);
    // dp[i]的含义为：只接区间 [0,i] 内乘客的最大盈利
    unordered_map<int, vector<vector<int>>> end;
    for (const auto& ride : rides)
    {
      // 记录有哪几个乘客在 ride[1] 地点下车
      end[ride[1]].push_back(ride);
    }
    for (int i = 1; i <= n; i++)
    {
      // 没有乘客在 i 地点下车
      dp[i] = dp[i - 1];
      for (const auto& ride : end[i])
      {
        // 尝试查找前面的乘客
        dp[i] = std::max(dp[i], dp[ride[0]] + ride[1] - ride[0] + ride[2]);
      }
    }
    return dp[n];
  }
};

void test()
{
  Solution s;
  vector<vector<int>> r1 = {{2, 5, 4}, {1, 5, 1}};
  vector<vector<int>> r2 = {{1, 6, 1}, {3, 10, 2}, {10, 12, 3}, {11, 12, 2}, {12, 15, 2}, {13, 18, 1}};
  EXPECT_EQ_INT(7, s.maxTaxiEarnings(5, r1));
  EXPECT_EQ_INT(20, s.maxTaxiEarnings(20, r2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
