#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  bool isHappy1(int n)
  {
    unordered_set<int> set;
    while (n != 1)
    {
      int sum = 0;
      while (n != 0)
      {
        int r = n % 10;
        sum += r * r;
        n /= 10;
      }
      n = sum;
      if (set.count(n))
      {
        break;
      }
      set.emplace(n);
    }
    return n == 1;
  }

  bool isHappy2(int n)
  {
    while (n != 1 && n != 4)
    {
      int sum = 0;
      while (n != 0)
      {
        sum += (n % 10) * (n % 10);
        n /= 10;
      }
      n = sum;
    }
    return n == 1;
  }
};

void testIsHappy()
{
  Solution s;
  EXPECT_TRUE(s.isHappy1(19));
  EXPECT_FALSE(s.isHappy1(2));
  EXPECT_TRUE(s.isHappy2(19));
  EXPECT_FALSE(s.isHappy2(2));
  EXPECT_SUMMARY;
}

int main()
{
  testIsHappy();
  return 0;
}
