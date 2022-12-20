#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

// https://leetcode.cn/problems/minimum-adjacent-swaps-for-k-consecutive-ones/solution/duo-tu-xin-shou-jiao-cheng-yi-bu-bu-dai-6bps4/

class Solution
{
 public:
  int minMoves(vector<int> &nums, int k)
  {
    // TODO
    return 0;
  }
};

void testMinMoves()
{
  Solution s;
  vector<int> n1 = {1, 0, 0, 1, 0, 1};
  vector<int> n2 = {1, 0, 0, 0, 0, 0, 1, 1};
  vector<int> n3 = {1, 1, 0, 1};
  EXPECT_EQ_INT(1, s.minMoves(n1, 2));
  EXPECT_EQ_INT(5, s.minMoves(n2, 3));
  EXPECT_EQ_INT(0, s.minMoves(n3, 2));
  EXPECT_SUMMARY;
}

int main()
{
  testMinMoves();
  return 0;
}
