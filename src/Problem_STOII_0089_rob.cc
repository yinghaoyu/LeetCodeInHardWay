#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/house-robber/
// @sa Problem_0198_rob.cc

class Solution
{
 public:
  int rob(vector<int> &nums)
  {
    if (nums.size() == 1)
    {
      return nums[0];
    }
    int n = nums.size();
    int pre = nums[0];
    int cur = std::max(nums[0], nums[1]);
    for (int i = 2; i < n; i++)
    {
      int next = std::max(cur, pre + nums[i]);
      pre = cur;
      cur = next;
    }
    return cur;
  }
};
