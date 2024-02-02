#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int jump(vector<int>& nums)
  {
    int ans = 0;
    int n = nums.size();
    int jump = 0;
    // 当前能跳到的最远距离
    int cur = 0;
    // 下一步能跳到的最远距离
    int next = 0;
    for (int i = 0; i < n; i++)
    {
      // 来到i下标
      // cur包括了i所在的位置，不用付出额外步数
      // cur没有包括i所在的位置，需要付出额外步数
      if (cur < i)
      {
        jump++;
        cur = next;
      }
      next = std::max(next, i + nums[i]);
    }
    return jump;
  }
};

void testJump()
{
  Solution s;
  vector<int> n1 = {2, 3, 1, 1, 4};
  vector<int> n2 = {2, 3, 0, 1, 4};
  vector<int> n3 = {1, 1, 1, 1, 1};
  vector<int> n4 = {3, 2, 1, 4, 5, 1, 1, 1, 3};
  EXPECT_EQ_INT(2, s.jump(n1));
  EXPECT_EQ_INT(2, s.jump(n2));
  EXPECT_EQ_INT(4, s.jump(n3));
  EXPECT_EQ_INT(3, s.jump(n4));
  EXPECT_SUMMARY;
}

int main()
{
  testJump();
  return 0;
}
