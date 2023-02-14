#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool canJump(vector<int> &nums)
  {
    // 如果某一个作为 起跳点 的格子可以跳跃的距离是 3，那么表示后面 3 个格子都可以作为 起跳点
    // 可以对每一个能作为 起跳点 的格子都尝试跳一次，把 能跳到最远的距离 不断更新
    // 如果可以一直跳到最后，就成功了
    int n = nums.size();
    int max = 0;
    for (int i = 0; i < n; i++)
    {
      if (max < i)
      {
        return false;
      }
      max = std::max(max, i + nums[i]);
    }
    return true;
  }
};

void testCanJump()
{
  Solution s;
  vector<int> n1 = {2, 3, 1, 1, 4};
  vector<int> n2 = {3, 2, 1, 0, 4};
  EXPECT_TRUE(s.canJump(n1));
  EXPECT_FALSE(s.canJump(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testCanJump();
  return 0;
}
