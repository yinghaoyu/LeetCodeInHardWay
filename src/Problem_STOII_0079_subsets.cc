#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/subsets/
// @sa Problem_0078_subsets.cc

class Solution
{
 public:
  vector<vector<int>> subsets(vector<int> &nums)
  {
    int n = nums.size();
    int mask = 1 << n;
    vector<vector<int>> ans;
    for (int i = 0; i < mask; i++)
    {
      vector<int> cur;
      for (int j = 0; j < n; j++)
      {
        if ((i >> j) & 1)
        {
          cur.push_back(nums[j]);
        }
      }
      ans.emplace_back(cur);
    }
    return ans;
  }
};
