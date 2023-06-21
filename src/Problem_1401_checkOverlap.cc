#include <algorithm>
#include <iostream>

#include "UnitTest.h"

using namespace std;

// https://leetcode.cn/problems/circle-and-rectangle-overlapping/solution/python3javacgotypescript-yi-ti-yi-jie-sh-vpsu/
class Solution
{
 public:
  bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2)
  {
    auto min = [](int left, int right, int k)
    {
      if (left <= k && k <= right)
      {
        return 0;
      }
      return k < left ? left - k : k - right;
    };

    int x = min(x1, x2, xCenter);
    int y = min(y1, y2, yCenter);
    return x * x + y * y <= radius * radius;
  }
};

void test()
{
  Solution s;
  EXPECT_TRUE(s.checkOverlap(1, 0, 0, 1, -1, 3, 1));
  EXPECT_FALSE(s.checkOverlap(1, 1, 1, 1, -3, 2, -1));
  EXPECT_TRUE(s.checkOverlap(1, 0, 0, -1, 0, 0, 1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
