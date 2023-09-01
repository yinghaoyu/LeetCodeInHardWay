#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 这题容易跟背包问题混淆
class Solution
{
 public:
  long long waysToBuyPensPencils(int total, int cost1, int cost2)
  {
    if (cost1 < cost2)
    {
      // 减少枚举次数
      return waysToBuyPensPencils(total, cost2, cost1);
    }
    long long ans = 0;
    // 枚举每次购买多少本笔记本
    for (int i = 0; i * cost1 <= total; i++)
    {
      // 每次购买 i 本笔记本后，剩下可购买几只钢笔，可以一只都不买，因此需要 + 1
      ans += (total - i * cost1) / cost2 + 1;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(9, s.waysToBuyPensPencils(20, 10, 5));
  EXPECT_EQ_INT(1, s.waysToBuyPensPencils(5, 10, 10));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
