
#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 陷阱，不考虑复杂度，这个写法也是错的，因为第一个元素必须选择！！！
  // 而下面这种解法，第一个元素可不选
  // long long maxScore(vector<int>& nums, int x)
  // {
  //   int n = nums.size();
  //   vector<long long> dp(n);
  //   dp[0] = nums[0];
  //   long long ans = 0;
  //   for (int i = 1; i < n; i++)
  //   {
  //     for (int j = 0; j < i; j++)
  //     {
  //       dp[i] = std::max(dp[i], nums[i] + dp[j] - ((nums[i] ^ nums[j]) & 1) * x);
  //     }
  //     ans = std::max(ans, dp[i]);
  //   }
  //   return ans;
  // }

  long long maxScore(vector<int>& nums, int x)
  {
    long long ans = nums[0];
    vector<long long> dp(2, INT32_MIN);
    int n = nums.size();
    dp[nums[0] % 2] = nums[0];
    for (int i = 1; i < n; i++)
    {
      int p = nums[i] % 2;
      // 分别从奇偶性考虑转移
      long long cur = std::max(dp[p] + nums[i], dp[1 - p] - x + nums[i]);
      ans = std::max(ans, cur);
      dp[p] = std::max(dp[p], cur);
    }
    return ans;
  }
};
