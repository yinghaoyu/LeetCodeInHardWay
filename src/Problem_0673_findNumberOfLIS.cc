#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 时间复杂度O(N^2)
  int findNumberOfLIS(vector<int> &nums)
  {
    int N = nums.size();
    // dp[i]表示必须以nums[i]为结尾的最长递增子序列
    vector<int> dp(N);
    // dp[i]表示必须以nums[i]为结尾的最长递增子序列的个数
    vector<int> count(N);
    for (int i = 0; i < N; i++)
    {
      dp[i] = 1;
      count[i] = 1;
      for (int j = 0; j < i; j++)
      {
        if (nums[j] < nums[i])
        {
          if (dp[j] + 1 > dp[i])
          {
            // 第一次找到
            dp[i] = dp[j] + 1;
            count[i] = count[j];
          }
          else if (dp[j] + 1 == dp[i])
          {
            // 再次找到
            count[i] += count[j];
          }
        }
      }
    }
    // 最后返回的值应该是所有最大长度的所有count的总和
    int max = *max_element(dp.begin(), dp.end());
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
      if (dp[i] == max)
      {
        ans += count[i];
      }
    }
    return ans;
  }
};

void testFindNumberOfLIS()
{
  Solution s;
  vector<int> n1 = {1, 3, 5, 4, 7};
  vector<int> n2 = {2, 2, 2, 2, 2};
  EXPECT_EQ_INT(2, s.findNumberOfLIS(n1));
  EXPECT_EQ_INT(5, s.findNumberOfLIS(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testFindNumberOfLIS();
  return 0;
}
