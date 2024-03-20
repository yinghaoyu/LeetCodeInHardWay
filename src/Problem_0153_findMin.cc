#include <cstdint>
#include <vector>

using namespace std;

class Solution
{
 public:
  //
  //        * |
  //      *   |
  //    *     |
  //  *       |
  // low      |      *
  //          |   *
  //          *  high
  //         min
  // 数组中的最后一个元素 x:
  // 在最小值右侧的元素（不包括最后一个元素本身），它们的值一定都严格小于x；
  // 而在最小值左侧的元素，它们的值一定都严格大于 x。

  int findMin(vector<int>& nums)
  {
    int n = nums.size();
    int l = 0;
    int r = n - 1;
    while (l < r)
    {
      int m = (r - l) / 2 + l;
      if (nums[m] < nums[n - 1])
      {
        // 说明最小值在左侧
        r = m;
      }
      else
      {
        l = m + 1;
      }
    }
    return nums[l];
  }
};
