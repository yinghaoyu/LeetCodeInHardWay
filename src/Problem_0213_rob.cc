#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int rob(vector<int> &nums)
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
  EXPECT_EQ_INT(3, s.rob(n1));
  EXPECT_EQ_INT(4, s.rob(n2));
  EXPECT_EQ_INT(3, s.rob(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testRob();
  return 0;
}
