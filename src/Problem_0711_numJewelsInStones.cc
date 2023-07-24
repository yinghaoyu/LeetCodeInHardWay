#include <iostream>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 针对 ASCII 码后 6 位
  // 000001 ~ 011010 (A ~ Z)
  // 100001 ~ 111010 (a ~ z)
  // 111010为 58 < 64，因此用 64 位数即可保存
  int numJewelsInStones(string jewels, string stones)
  {
    long long mask = 0;
    int ans = 0;
    for (auto &c : jewels)
    {
      mask |= (1LL << (c & 63));
    }
    for (auto &c : stones)
    {
      ans += ((mask >> (c & 63)) & 1);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(3, s.numJewelsInStones("aA", "aAAbbbb"));
  EXPECT_EQ_INT(0, s.numJewelsInStones("z", "ZZ"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
