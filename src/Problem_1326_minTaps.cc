#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minTaps(int n, vector<int> &ranges)
  {
    vector<int> right_most(n + 1);
    for (int i = 0; i <= n; ++i)
    {
      int r = ranges[i];
      if (i > r)
      {
        right_most[i - r] = i + r;  // 对于 i-r 来说，i+r 必然是它目前的最大值
      }
      else
      {
        right_most[0] = std::max(right_most[0], i + r);
      }
    }

    int ans = 0;
    int cur_right = 0;   // 已建造的桥的右端点
    int next_right = 0;  // 下一座桥的右端点的最大值
    for (int i = 0; i < n; ++i)
    {
      // 注意这里没有遍历到 n，因为它已经是终点了
      next_right = std::max(next_right, right_most[i]);
      if (i == cur_right)
      {
        // 到达已建造的桥的右端点
        if (i == next_right)
        {
          // 无论怎么造桥，都无法从 i 到 i+1
          return -1;
        }
        // 造一座桥
        cur_right = next_right;
        ++ans;
      }
    }
    return ans;
  }
};

void testMinTaps()
{
  Solution s;
  vector<int> r1 = {3, 4, 1, 1, 0, 0};
  vector<int> r2 = {0, 0, 0, 0};
  EXPECT_EQ_INT(1, s.minTaps(5, r1));
  EXPECT_EQ_INT(-1, s.minTaps(3, r2));
  EXPECT_SUMMARY;
}

int main()
{
  testMinTaps();
  return 0;
}
