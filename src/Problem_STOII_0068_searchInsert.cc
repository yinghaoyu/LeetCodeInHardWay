#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0035
// https://leetcode-cn.com/problems/search-insert-position/
// see at Problem_0035_searchInsert.cc
class Solution
{
 public:
  int searchInsert(vector<int> &nums, int target)
  {
    int left = 0;
    int right = nums.size() - 1;
    int index = nums.size();
    while (left <= right)
    {
      int mid = (right - left) / 2 + left;
      if (target <= nums[mid])
      {
        index = mid;
        right = mid - 1;
      }
      else
      {
        left = mid + 1;
      }
    }
    return index;
  }
};
