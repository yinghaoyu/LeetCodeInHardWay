#include <vector>

using namespace std;

// 第 153 题的进阶题
// 旋转数组
class Solution
{
 public:
  int findMin(vector<int>& nums)
  {
    int l = 0;
    int r = nums.size() - 1;
    while (l < r)
    {
      int m = (r - l) / 2 + l;
      if (nums[m] < nums[r])
      {
        // 说明最小值在 [0..m]
        r = m;
      }
      else if (nums[m] > nums[r])
      {
        // 说明最小值在 [m+1, r]
        l = m + 1;
      }
      else
      {
        // 说明有重复的值，那么忽视当前重复的值也不会影响结果
        r--;
      }
    }
    return nums[l];
  }
};
