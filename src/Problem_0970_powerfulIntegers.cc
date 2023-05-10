#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 枚举
  vector<int> powerfulIntegers(int x, int y, int bound)
  {
    unordered_set<int> cnt;
    int a = 1;
    for (int i = 0; i < 21; i++)
    {
      int b = 1;
      for (int j = 0; j < 21; j++)
      {
        int value = a + b;
        if (value <= bound)
        {
          cnt.emplace(value);
        }
        else
        {
          break;
        }
        b *= y;
      }
      if (a > bound)
      {
        break;
      }
      a *= x;
    }
    return vector<int>(cnt.begin(), cnt.end());
  }
};

void testPowerfulInteger()
{
  Solution s;
  vector<int> o1 = {2, 3, 4, 5, 7, 9, 10};
  vector<int> o2 = {2, 4, 6, 8, 10, 14};

  vector<int> a = s.powerfulIntegers(2, 3, 10);
  std::sort(a.begin(), a.end());

  vector<int> b = s.powerfulIntegers(3, 5, 15);
  std::sort(b.begin(), b.end());

  EXPECT_TRUE(o1 == a);
  EXPECT_TRUE(o2 == b);
  EXPECT_SUMMARY;
}

int main()
{
  testPowerfulInteger();
  return 0;
}
