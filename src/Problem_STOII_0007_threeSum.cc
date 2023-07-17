#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 与 leetcode 0015 相同
// https://leetcode.cn/problems/3sum/
// see at Problem_0015_threeSum.cc
class Solution
{
 private:
  vector<vector<int>> binarySearch(vector<int> &nums, int begin, int target)
  {
    int n = nums.size();
    int left = begin;
    int right = n - 1;
    vector<vector<int>> ans;
    while (left < right)
    {
      int sum = nums[left] + nums[right];
      if (sum < target)
      {
        left++;
      }
      else if (sum > target)
      {
        right--;
      }
      else
      {
        if (left == begin || nums[left - 1] != nums[left])
        {
          ans.push_back({nums[left], nums[right]});
        }
        left++;
      }
    }
    return ans;
  }

 public:
  vector<vector<int>> threeSum(vector<int> &nums)
  {
    int n = nums.size();
    vector<vector<int>> ans;
    std::sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++)
    {
      if (i == 0 || nums[i - 1] != nums[i])
      {
        vector<vector<int>> arr = binarySearch(nums, i + 1, -nums[i]);
        for (auto &x : arr)
        {
          x.push_back(nums[i]);
          ans.push_back(x);
        }
      }
    }
    return ans;
  }
};
