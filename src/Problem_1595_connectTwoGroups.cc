#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// https://leetcode.cn/problems/minimum-cost-to-connect-two-groups-of-points/solution/lian-tong-liang-zu-dian-de-zui-xiao-chen-6qoj/
class Solution
{
 public:
  // TODO: conquer it
  int connectTwoGroups(vector<vector<int>> &cost)
  {
    int n = cost.size();
    int m = cost[0].size();
    int mask = 1 << m;
    vector<vector<int>> dp(n + 1, vector<int>(mask, INT32_MAX >> 1));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
      for (int s = 0; s < mask; s++)
      {
        for (int k = 0; k < m; k++)
        {
          if ((s & (1 << k)) == 0)
          {
            continue;
          }
          dp[i][s] = std::min(dp[i][s], dp[i][s ^ (1 << k)] + cost[i - 1][k]);
          dp[i][s] = std::min(dp[i][s], dp[i - 1][s] + cost[i - 1][k]);
          dp[i][s] = std::min(dp[i][s], dp[i - 1][s ^ (1 << k)] + cost[i - 1][k]);
        }
      }
    }
    return dp[n][mask - 1];
  }
};

void test()
{
  Solution s;
  vector<vector<int>> n1 = {{15, 96}, {36, 2}};
  vector<vector<int>> n2 = {{1, 3, 5}, {4, 1, 1}, {1, 5, 3}};
  vector<vector<int>> n3 = {{2, 5, 1}, {3, 4, 7}, {8, 1, 2}, {6, 2, 4}, {3, 8, 8}};
  EXPECT_EQ_INT(17, s.connectTwoGroups(n1));
  EXPECT_EQ_INT(4, s.connectTwoGroups(n2));
  EXPECT_EQ_INT(10, s.connectTwoGroups(n3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
