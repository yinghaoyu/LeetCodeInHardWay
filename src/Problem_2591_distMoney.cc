#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int distMoney(int money, int children)
  {
    if (money < children)
    {
      // 不合法
      return -1;
    }
    // 先每个人分配 1 块，保证每个人至少有 1 块
    money -= children;
    // 按最大可能每人分配 7 块
    int cnt = std::min(money / 7, children);
    money -= 7 * cnt;
    children -= cnt;
    if ((children == 0 && money > 0) || (children == 1 && money == 3))
    {
      cnt--;
    }
    return cnt;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(1, s.distMoney(20, 3));
  EXPECT_EQ_INT(2, s.distMoney(16, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
