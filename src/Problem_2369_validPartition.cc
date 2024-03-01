#include <vector>

using namespace std;

class Solution
{
 public:
  // 打麻将问题
  bool validPartition(vector<int>& nums)
  {
    int n = nums.size();
    // dp[i]的含义为：nums[0...i]区间是否满足拆分条件
    vector<bool> dp(n + 1, false);
    // base case
    dp[0] = true;
    for (int i = 1; i <= n; i++)
    {
      if (i >= 2)
      {
        // 前面满足条件，后面两个数相等
        dp[i] = dp[i - 2] && isValid(nums[i - 2], nums[i - 1]);
      }
      if (i >= 3)
      {
        // 前面满足条件，后面3个数相等或者是递增顺子
        dp[i] = dp[i] || (dp[i - 3] && isValid(nums[i - 3], nums[i - 2], nums[i - 1]));
      }
    }
    return dp[n];
  }

  bool isValid(int a, int b) { return a == b; }

  bool isValid(int a, int b, int c) { return (a == b && b == c) || (a + 1 == b && b + 1 == c); }
};
