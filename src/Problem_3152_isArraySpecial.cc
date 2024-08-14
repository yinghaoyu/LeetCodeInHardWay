#include <vector>

using namespace std;

class Solution
{
 public:
  vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries)
  {
    int n = nums.size();
    // dp[i]表示必须以nums[i]为结尾，最长特殊数组的长度
    vector<int> dp(n);
    // 当只有一个元素时，明显符合特殊数组
    dp[0] = true;
    for (int i = 1; i < n; i++)
    {
      // 讨论nums[i]与左边相邻元素nums[i-1]的奇偶性
      // 情况一：如果奇偶性相同，此时dp[i]=1
      // 情况二：如果奇偶性不同，此时dp[i]=dp[i-1]+1
      dp[i] = (nums[i] ^ nums[i - 1]) & 1 ? dp[i - 1] + 1 : 1;
    }

    vector<bool> ans;
    for (auto& q : queries)
    {
      int i = q[0];
      int j = q[1];
      ans.emplace_back(dp[j] >= j - i + 1);
    }
    return ans;
  }
};
