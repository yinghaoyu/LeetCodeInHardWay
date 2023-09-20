#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minCount(vector<int> &coins)
  {
    int ans = 0;
    for (auto &x : coins)
    {
      ans += (x + 1) >> 1;
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> c1 = {4, 2, 1};
  vector<int> c2 = {2, 3, 10};
  EXPECT_EQ_INT(4, s.minCount(c1));
  EXPECT_EQ_INT(8, s.minCount(c2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
