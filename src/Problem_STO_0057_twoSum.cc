#include <iostream>
#include <vector>

using namespace std;

class Solution
{
 public:
  int binarySearch(vector<int> &nums, int begin, int target)
  {
    int left = begin;
    int right = nums.size() - 1;
    int index = -1;
    while (left <= right)
    {
      int mid = left + (right - left) / 2;
      if (nums[mid] < target)
      {
        left = mid + 1;
      }
      else if (nums[mid] > target)
      {
        right = mid - 1;
      }
      else
      {
        index = mid;
        break;
      }
    }
    return index;
  }

  vector<int> twoSum(vector<int> &nums, int target)
  {
    vector<int> ans;
    for (int i = 0; i < nums.size(); i++)
    {
      if (i == 0 || nums[i - 1] != nums[i])
      {
        int index = binarySearch(nums, i + 1, target - nums[i]);
        if (index != -1)
        {
          ans.push_back(nums[i]);
          ans.push_back(nums[index]);
          break;
        }
      }
    }
    return ans;
  }
};
