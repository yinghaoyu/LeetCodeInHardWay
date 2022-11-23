#include <iostream>
#include <unordered_map>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int getIndex(int x)
  {
    int ans = 0;
    while (x)
    {
      ans += x % 10;
      x /= 10;
    }
    return ans;
  }

  int countBalls(int lowLimit, int highLimit)
  {
    int n = highLimit - lowLimit + 1;
    unordered_map<int, int> boxs;
    int max = 0;
    for (int i = lowLimit; i <= highLimit; i++)
    {
      int idx = getIndex(i);
      boxs[idx]++;
      max = std::max(max, boxs[idx]);
    }
    return max;
  }
};

void testCountBalls()
{
  Solution s;
  EXPECT_EQ_INT(2, s.countBalls(1, 10));
  EXPECT_EQ_INT(2, s.countBalls(5, 15));
  EXPECT_EQ_INT(2, s.countBalls(19, 28));
  EXPECT_EQ_INT(1, s.countBalls(4, 7));
  EXPECT_SUMMARY;
}

int main()
{
  testCountBalls();
  return 0;
}
