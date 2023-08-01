#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // TODO: figure it out
  int sumOfPower(vector<int> &nums)
  {
    int n = nums.size();
    // 题设要求的是子序列不是子数组，所以排序后不影响结果
    std::sort(nums.begin(), nums.end());
    // dp[i] 表示 必须以 nums[i] 为结尾的序列，所有序列的最小值的和
    vector<int> dp(n);
    // sum[i] 表示 nums[0 ... i-1] 的前缀和
    vector<int> sum(n + 1);
    int ans = 0;
    const int mod = 1e9 + 7;
    for (int i = 0; i < n; i++)
    {
      dp[i] = (nums[i] + sum[i]) % mod;
      sum[i + 1] = (sum[i] + dp[i]) % mod;
      ans = (ans + nums[i] * nums[i] * dp[i]) % mod;
      if (ans < 0)
      {
        ans += mod;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {2, 1, 4};
  vector<int> n2 = {1, 1, 1};
  EXPECT_EQ_INT(141, s.sumOfPower(n1));
  EXPECT_EQ_INT(7, s.sumOfPower(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
