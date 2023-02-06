#include <vector>
#include <algorithm>
#include <iostream>
#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int getMaximumConsecutive(vector<int> &coins)
  {
    // [l, r]表示一段连续的区间
    // 不妨设现在能构造出的区间为 [0, x]
    // 我们新加入一个硬币面值为y
    // 那么可以构造出的区间为 [0, x] 和 [y, x + y]
    // 那么如果 y <= x + 1，这两个区间可以合并成连续的区间[0, x + y]
    // 否则只能构造出 [0, x] 区间，[y, x + y]舍去
    // 根据条件 y <= x + 1，每次选出最小硬币面值y才可尽量达到条件
    int ans = 1;
    std::sort(coins.begin(), coins.end());
    for(auto& i : coins)
    {
      if(i > ans)
      {
        break;
      }
      ans += i;
    }
    return ans;
  }
};

void testGetMaximumConsecutive()
{
  Solution s;
  vector<int> n1 = {1, 3};
  vector<int> n2 = {1, 1, 1, 4};
  vector<int> n3 = {1,89,8,1,47,34,99,1,1,1,55,89,1,52,36,1,62,1,1,1,4,27,1,45,1,1,48,1,94,1,63};
  EXPECT_EQ_INT(2, s.getMaximumConsecutive(n1));
  EXPECT_EQ_INT(8, s.getMaximumConsecutive(n2));
  EXPECT_EQ_INT(868, s.getMaximumConsecutive(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testGetMaximumConsecutive();
  return 0;
}
