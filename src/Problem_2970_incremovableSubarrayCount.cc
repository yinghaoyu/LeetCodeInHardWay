#include <vector>

using namespace std;

class Solution
{
 public:
  int incremovableSubarrayCount(vector<int>& nums)
  {
    int l = 1;
    int ans = 0;
    int n = nums.size();
    while (l < n && nums[l - 1] < nums[l])
    {
      l++;
    }
    // [l-1, n-1]
    // [l-2, n-1]
    // [0, n-1] 都是移除递增子数组
    // 若 l < n，那么 [l, n-1]也是
    ans += l + (l < n);
    // 枚举右边界
    for (int r = n - 2; r >= 0; r--)
    {
      // 左边已经是有序，找到第一个满足 nums[l-1] < nums[r+1] 的 l
      while (l > 0 && nums[l - 1] >= nums[r + 1])
      {
        l--;
      }
      // [l-1, r]
      // [l-2, r]
      // [0, r]都是移除递增子数组
      // 若 l <= r，那么[l,r]也是
      ans += l + (l <= r);
      if (r >= 0 && nums[r] >= nums[r + 1])
      {
        break;
      }
    }
    return ans;
  }
};
