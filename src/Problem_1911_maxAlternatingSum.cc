#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  long long maxAlternatingSum(vector<int> &nums)
  {
    int n = nums.size();
    // dp[i][0] 表示在 [0,i]中选一个子序列，并且选择的子序列的最后一个元素的下标为偶数的最大交替和
    // dp[i][1] 表示在 [0,i]中选一个子序列，并且选择的子序列的最后一个元素的下标为奇数的最大交替和
    vector<vector<long long>> dp(n, vector<long long>(2));
    dp[0][0] = nums[0];
    dp[0][1] = 0;
    for (int i = 1; i < n; i++)
    {
      // 可以空间优化
      dp[i][0] = std::max(dp[i - 1][0], dp[i - 1][1] + nums[i]);
      dp[i][1] = std::max(dp[i - 1][1], dp[i - 1][0] - nums[i]);
    }
    return dp[n - 1][0];
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {4, 2, 5, 3};
  vector<int> n2 = {5, 6, 7, 8};
  vector<int> n3 = {6, 2, 1, 2, 4, 5};
  EXPECT_EQ_INT(7, s.maxAlternatingSum(n1));
  EXPECT_EQ_INT(8, s.maxAlternatingSum(n2));
  EXPECT_EQ_INT(10, s.maxAlternatingSum(n3));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
