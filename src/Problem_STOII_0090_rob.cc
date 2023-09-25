#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/house-robber-ii/
// @sa Problem_0213_rob.cc

class Solution
{
 public:
  int rob(vector<int> &nums)
  {
    if (nums.size() == 1)
    {
      return nums[0];
    }
    if (nums.size() == 2)
    {
      return std::max(nums[0], nums[1]);
    }
    int n = nums.size();
    int pre = nums[0];
    int cur = std::max(nums[0], nums[1]);
    int ans = 0;
    for (int i = 2; i < n - 1; i++)
    {
      int next = std::max(cur, pre + nums[i]);
      pre = cur;
      cur = next;
    }
    int ans1 = cur;
    pre = nums[1];
    cur = std::max(nums[1], nums[2]);
    for (int i = 3; i < n; i++)
    {
      int next = std::max(cur, pre + nums[i]);
      pre = cur;
      cur = next;
    }
    int ans2 = cur;
    return std::max(ans1, ans2);
  }
};
