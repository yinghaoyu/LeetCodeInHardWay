#include <vector>

using namespace std;

class Solution
{
 public:
  // http://leetcode.cn/problems/largest-element-in-an-array-after-merge-operations/s

  // 从 i 开始，只要 nums[i−1] ≤ nums[i]，就不断向左合并数字，i=0,1,2,⋯,n−1
  // 开始向左合并，取合并结果的最大值作为答案。这样时间复杂度O(n^2)，太慢了。

  // 如果我们从 i=n−1 开始向左合并，合并到 j(j>0) 停止，
  // 这意味着 nums[j−1]>nums[j]+nums[j+1]+⋯+nums[n−1]
  // 所以从 i=n−2,n−3,⋯ ,j 开始向左合并，是不会合并出更大的数的，因为 nums
  // 中的元素都是正数，这样合并出来的数字只会更小，永远不会比 nums[j−1] 更大。

  // 所以无需枚举 i=n−2,n−3,⋯ ,j，而是直接从 i=j−1 开始向左合并，
  // 并且合并出的数字一定比从 i=n−1 开始更大。

  long long maxArrayValue(vector<int>& nums)
  {
    long long sum = nums.back();
    for (int i = nums.size() - 2; i >= 0; i--)
    {
      sum = nums[i] <= sum ? sum + nums[i] : nums[i];
    }
    return sum;
  }
};
