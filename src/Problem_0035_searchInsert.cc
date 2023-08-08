#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  int searchInsert(vector<int> &nums, int target)
  {
    int left = 0;
    int right = nums.size() - 1;
    // 注意这里的 index 初始值为 nums.size()，因为当 target <= nums[mid] 时，会更新 index
    // 而当 nums[mid] < target 时，是不会更新 index 的，所以当 target 比 nums 所有数都大时，结果就是插入数组末尾
    int index = nums.size();
    while (left <= right)
    {
      int mid = (right - left) / 2 + left;
      if (target <= nums[mid])
      {
        // 找到最左边的位置
        // 即找到第一个 >= target的位置
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
