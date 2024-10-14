#include <stdint.h>
#include <algorithm>
#include <vector>

using namespace std;

// 与Problem_1521_minimumDifference.cc解法相同
class Solution
{
 public:
  int minimumDifference(vector<int>& nums, int k)
  {
    int ans = INT32_MAX;
    for (int i = 0; i < nums.size(); i++)
    {
      int x = nums[i];
      ans = min(ans, abs(x - k));
      // 如果 x 是 nums[j] 的子集，就退出循环
      for (int j = i - 1; j >= 0 && (nums[j] | x) != nums[j]; j--)
      {
        nums[j] |= x;
        ans = min(ans, abs(nums[j] - k));
      }
    }
    return ans;
  }
};
