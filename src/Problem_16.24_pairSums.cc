#include <algorithm>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/
// @sa Problem_0167_twoSum.cc
class Solution
{
 public:
  // 双指针
  vector<vector<int>> pairSums(vector<int>& nums, int target)
  {
    std::sort(nums.begin(), nums.end());
    int n = nums.size();
    vector<vector<int>> ans;
    int l = 0;
    int r = n - 1;
    while (l < r)
    {
      if (nums[l] + nums[r] == target)
      {
        ans.push_back({nums[l], nums[r]});
        l++;
        r--;
      }
      else if (nums[l] + nums[r] < target)
      {
        l++;
      }
      else
      {
        r--;
      }
    }
    return ans;
  }
};
