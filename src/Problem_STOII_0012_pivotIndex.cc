#include <iostream>
#include <vector>

using namespace std;

// 与 leetcode 724 相同
// https://leetcode.cn/problems/find-pivot-index/
// see at Problem_0724_pivotIndex.cc
class Solution
{
 public:
  int pivotIndex(vector<int> &nums)
  {
    int n = nums.size();
    int all = 0;
    for (int i = 0; i < n; i++)
    {
      all += nums[i];
    }
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
      if (2 * sum + nums[i] == all)
      {
        return i;
      }
      sum += nums[i];
    }
    return -1;
  }
};
