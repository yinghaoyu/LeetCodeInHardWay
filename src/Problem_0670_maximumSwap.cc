#include <algorithm>
#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 贪心，时间复杂度log10(num)
  int maximumSwap(int num)
  {
    string str = std::to_string(num);
    int n = str.length();
    int maxIdx = n - 1;
    int idx1 = -1, idx2 = -1;
    for (int i = n - 1; i >= 0; i--)
    {
      // 从低位往高位找最大值
      if (str[i] > str[maxIdx])
      {
        maxIdx = i;
      }
      else if (str[i] < str[maxIdx])
      {
        // 最大值往高位交换能获得最优
        idx1 = i;
        idx2 = maxIdx;
      }
    }
    if (idx1 >= 0)
    {
      std::swap(str[idx1], str[idx2]);
      return stoi(str);
    }
    else
    {
      return num;
    }
  }
};

void testMaximumSwap()
{
  Solution s;
  EXPECT_EQ_INT(-3979, s.maximumSwap(-9973));
  EXPECT_EQ_INT(7236, s.maximumSwap(2736));
  EXPECT_EQ_INT(9973, s.maximumSwap(9973));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximumSwap();
  return 0;
}
