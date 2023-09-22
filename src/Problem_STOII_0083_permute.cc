#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/permutations/
// @sa Problem_0046_permute.cc

class Solution
{
 public:
  void process(vector<int> &nums, int index, vector<vector<int>> &ans)
  {
    if (index == nums.size())
    {
      ans.push_back(nums);
      return;
    }
    for (int i = index; i < nums.size(); i++)
    {
      swap(nums[index], nums[i]);
      process(nums, index + 1, ans);
      swap(nums[index], nums[i]);
    }
  }

  vector<vector<int>> permute(vector<int> &nums)
  {
    vector<vector<int>> ans;
    process(nums, 0, ans);
    return ans;
  }
};
