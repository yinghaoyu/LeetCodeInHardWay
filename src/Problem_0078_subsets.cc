#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 二进制枚举
  vector<vector<int>> subsets1(vector<int> &nums)
  {
    int mask = 1 << nums.size();
    vector<vector<int>> ans;
    for (int i = 0; i < mask; i++)
    {
      vector<int> cur;
      for (int j = 0; j < nums.size(); j++)
        if ((i >> j) & 1)
        {
          cur.push_back(nums[j]);
        }
      ans.emplace_back(cur);
    }
    return ans;
  }

  void process(vector<int> &nums, int index, vector<int> &cur, vector<vector<int>> &ans)
  {
    if (index == nums.size())
    {
      ans.push_back(cur);
      return;
    }
    // 不取index位置
    process(nums, index + 1, cur, ans);
    // 取index位置
    cur.push_back(nums[index]);
    process(nums, index + 1, cur, ans);
    cur.pop_back();
  }

  // 递归
  vector<vector<int>> subsets2(vector<int> &nums)
  {
    vector<vector<int>> ans;
    vector<int> cur;
    process(nums, 0, cur, ans);
    return ans;
  }
};
