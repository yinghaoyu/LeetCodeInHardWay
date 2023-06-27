#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maximumSum(vector<int> &arr)
  {
    int n = arr.size();
    // dp[i][j]的含义为以 arr[i] 结尾(删除前)，删除 j 次的非空子数组的最大和
    vector<vector<int>> dp(n, vector<int>(2));
    dp[0][0] = arr[0];
    dp[0][1] = 0;
    int ans = arr[0];
    for (int i = 1; i < n; i++)
    {
      dp[i][0] = std::max(dp[i - 1][0], 0) + arr[i];
      dp[i][1] = std::max(dp[i - 1][1] + arr[i], dp[i - 1][0]);
      ans = std::max(ans, std::max(dp[i][0], dp[i][1]));
    }
    return ans;
  }

  // 空间优化
  int dp(vector<int> &arr)
  {
    int n = arr.size();
    int dp0 = arr[0];
    int dp1 = 0;
    int ans = arr[0];
    for (int i = 1; i < n; i++)
    {
      dp1 = std::max(dp1 + arr[i], dp0);
      dp0 = std::max(dp0, 0) + arr[i];
      ans = std::max(ans, std::max(dp0, dp1));
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {1, -2, 0, 3};
  vector<int> n2 = {1, -2, -2, 3};
  vector<int> n3 = {-1, -1, -1, -1};
  EXPECT_EQ_INT(4, s.maximumSum(n1));
  EXPECT_EQ_INT(3, s.maximumSum(n2));
  EXPECT_EQ_INT(-1, s.maximumSum(n3));
  EXPECT_EQ_INT(4, s.dp(n1));
  EXPECT_EQ_INT(3, s.dp(n2));
  EXPECT_EQ_INT(-1, s.dp(n3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
