#include <vector>

using namespace std;

// 旋转数组
// 此题是第 33 题的进阶版，nums中的数可能相同
class Solution
{
 public:
  bool search(vector<int>& nums, int target)
  {
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    while (l <= r)
    {
      int m = (r - l) / 2 + l;
      if (nums[m] == target)
      {
        return true;
      }
      if (nums[l] == nums[m] && nums[m] == nums[r])
      {
        // 比第 33 题多了这一步，缩小当前区间
        ++l;
        --r;
      }
      else if (nums[l] <= nums[m])
      {
        // 左边有序
        if (nums[l] <= target && target < nums[m])
        {
          r = m - 1;
        }
        else
        {
          l = m + 1;
        }
      }
      else
      {
        // 右边有序
        if (nums[m] < target && target <= nums[r])
        {
          l = m + 1;
        }
        else
        {
          r = m - 1;
        }
      }
    }
    return false;
  }
};
