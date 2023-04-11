#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // instructions可以简化为一个向量跟最终面朝方向。
  // 如果最终面朝方向与原始面朝方向垂直，那么机器人走四次instructions会回到原点形成闭环。（四个向量组成一个正方形）
  // 如果最终面朝方向是原始面朝方向的反方向，则下一次instructions必定会到原点。（两个方向相反的向量）
  // 如果面朝方向不变，向量不是零则发散，是零则一直在原点。
  bool isRobotBounded(string instructions)
  {
    // ↑ → ↓ ←
    vector<vector<int>> direction = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int x = 0;
    int y = 0;
    int dir = 0;
    for (auto &c : instructions)
    {
      if (c == 'G')
      {
        x += direction[dir][0];
        y += direction[dir][1];
      }
      else if (c == 'L')
      {
        dir = (dir + 3) % 4;
      }
      else
      {
        dir = (dir + 1) % 4;
      }
    }
    if (dir == 0)
    {
      return x == 0 && y == 0;
    }
    return true;
  }
};

void testIsRobotBounded()
{
  Solution s;
  EXPECT_TRUE(s.isRobotBounded("GGLLGG"));
  EXPECT_FALSE(s.isRobotBounded("GG"));
  EXPECT_TRUE(s.isRobotBounded("GL"));
  EXPECT_SUMMARY;
}

int main()

{
  testIsRobotBounded();
  return 0;
}
