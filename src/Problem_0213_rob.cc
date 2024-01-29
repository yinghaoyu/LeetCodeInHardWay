#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int rob1(vector<int>& nums)
  {
    int n = nums.size();
    if (n == 1)
    {
      return nums[0];
    }
    return std::max(best(nums, 1, n - 1), nums[0] + best(nums, 2, n - 2));
  }

  // nums[l....r]范围上，没有环形的概念
  // 返回 : 可以随意选择数字，但不能选择相邻数字的情况下，最大累加和
  int best(vector<int>& nums, int l, int r)
  {
    if (l > r)
    {
      return 0;
    }
    if (l == r)
    {
      return nums[l];
    }
    if (l + 1 == r)
    {
      return std::max(nums[l], nums[r]);
    }
    int prepre = nums[l];
    int pre = std::max(nums[l], nums[l + 1]);
    for (int i = l + 2, cur; i <= r; i++)
    {
      cur = std::max(pre, nums[i] + std::max(0, prepre));
      prepre = pre;
      pre = cur;
    }
    return pre;
  }

  // 动态规划
  int rob2(vector<int>& nums)
  {
    if (nums.size() == 0)
    {
      return 0;
    }
    if (nums.size() == 1)
    {
      return nums[0];
    }
    if (nums.size() == 2)
    {
      return std::max(nums[0], nums[1]);
    }
    int pre2 = nums[0];
    int pre1 = std::max(nums[0], nums[1]);
    for (int i = 2; i < nums.size() - 1; i++)
    {
      int tmp = std::max(pre1, nums[i] + pre2);
      pre2 = pre1;
      pre1 = tmp;
    }
    int ans1 = pre1;
    pre2 = nums[1];
    pre1 = std::max(nums[1], nums[2]);
    for (int i = 3; i < nums.size(); i++)
    {
      int tmp = std::max(pre1, nums[i] + pre2);
      pre2 = pre1;
      pre1 = tmp;
    }
    int ans2 = pre1;
    return std::max(ans1, ans2);
  }
};

void testRob()
{
  Solution s;
  vector<int> n1 = {2, 3, 2};
  vector<int> n2 = {1, 2, 3, 1};
  vector<int> n3 = {1, 2, 3};
  EXPECT_EQ_INT(3, s.rob2(n1));
  EXPECT_EQ_INT(4, s.rob2(n2));
  EXPECT_EQ_INT(3, s.rob2(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testRob();
  return 0;
}
