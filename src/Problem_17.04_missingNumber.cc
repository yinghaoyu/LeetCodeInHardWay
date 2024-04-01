#include <vector>

using namespace std;

// @sa Problem_0041_firstMissingPositive.cc
class Solution
{
 public:
  int missingNumber(vector<int>& nums)
  {
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      // nums[i] >= 0 && nums[i] < n 保证 nums[i] 在区间内
      while (nums[i] >= 0 && nums[i] < n && nums[i] != nums[nums[i]])
      {
        swap(nums[i], nums[nums[i]]);
      }
    }
    for (int i = 0; i < n; i++)
    {
      if (nums[i] != i)
      {
        return i;
      }
    }
    return n;
  }
};
