#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/single-element-in-a-sorted-array/
// @sa Problem_0540_singleNonDuplicate.cc

class Solution
{
 public:
  int singleNonDuplicate(vector<int> &nums)
  {
    // 假设下标 x 位置的数不同，可以发现，
    // 位于 x 位置左边的数，nums[y] = nums[y+1]，y一定是偶数
    // 位于 y 位置右边的数，nums[y] = nums[y+1]，y一定是奇数
    // 那么可以利用这一性质，
    // 当 y 为偶数时，可以判断 nums[y] == nums[y+1]，如果符合，说明当前在 x 的左侧
    // 当 y 为奇数时，可以判断 nums[y-1] == nums[y]，如果符合，说明当前在 x 的左侧
    // 已知，对于偶数 y + 1 = y ^ 1，对于奇数 y - 1 = y ^ 1，因此可直接计算 y ^ 1来得到下标
    int left = 0;
    int right = nums.size() - 1;
    while (left < right)
    {
      int mid = (right - left) / 2 + left;
      if (nums[mid] == nums[mid ^ 1])
      {
        left = mid + 1;
      }
      else
      {
        right = mid;
      }
    }
    return nums[left];
  }
};
