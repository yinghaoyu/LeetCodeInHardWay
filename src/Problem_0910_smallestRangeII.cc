#include <algorithm>
#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/smallest-range-ii/solutions/2928780/xiao-de-bian-da-da-de-bian-xiao-pythonja-8fnp/?envType=daily-question&envId=2024-10-21
class Solution
{
 public:
  int smallestRangeII(vector<int>& nums, int k)
  {
    std::sort(nums.begin(), nums.end());
    int ans = nums.back() - nums[0];
    // 如果把所有数都变小或者变大，结果都是max - min
    // 如果大的变大，小的变小，max - min会变大，明显不符合题意
    // 把小的变大，把大的变小，这样才可能使得 max - min 变小
    // 枚举把num[0...i-1]的元素变大，nums[i...n-1]变小的所有可能性
    for (int i = 1; i < nums.size(); i++)
    {
      // 调整后，最大值只可能是nums[i-1] + k 与 nums.back() - k 的其中一个
      int max = std::max(nums[i - 1] + k, nums.back() - k);
      // 调整后，最小值只可能是nums[0] + k 与 nums[i] - k 的其中一个
      int min = std::min(nums[0] + k, nums[i] - k);
      ans = std::min(ans, max - min);
    }
    return ans;
  }
};
