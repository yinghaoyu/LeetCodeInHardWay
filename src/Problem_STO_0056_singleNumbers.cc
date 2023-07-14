#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int lowBit(int x) { return x & -x; }

  vector<int> singleNumbers(vector<int> &nums)
  {
    int xorALL = 0;
    for (auto &num : nums)
    {
      xorALL ^= num;
    }
    int x = lowBit(xorALL);
    int first = 0;
    for (auto &num : nums)
    {
      if (x & num)
      {
        first ^= num;
      }
    }
    int second = xorALL ^ first;
    return {first, second};
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {4, 1, 4, 6};
  vector<int> n2 = {1, 2, 10, 4, 1, 4, 3, 3};
  vector<int> o1 = {1, 6};
  vector<int> o2 = {10, 2};
  EXPECT_TRUE(o1 == s.singleNumbers(n1));
  EXPECT_TRUE(o2 == s.singleNumbers(n2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
