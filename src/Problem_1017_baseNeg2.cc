#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 除基取余法
  // a = (-2) * b + c
  // a - (-2) * b = c
  // a - (-2) * b + 2 = c + 2
  // a - (-2) * (b + 1) = c + 2
  // 负二进制的余数可能有0，1，-1，而表示上不能有负数，所以在余数为-1时，要转化为1，同时商+1
  string baseNeg2(int n)
  {
    int a = 0;
    int b = 0;
    string ans;
    while (n != 0)
    {
      int remain = n % -2;
      ans += '0' + std::abs(remain);
      n /= -2;
      if (remain < 0)
      {
        n++;
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};

void testBaseNeg2()
{
  Solution s;
  EXPECT_TRUE("110" == s.baseNeg2(2));
  EXPECT_TRUE("111" == s.baseNeg2(3));
  EXPECT_TRUE("100" == s.baseNeg2(4));
  EXPECT_SUMMARY;
}

int main()
{
  testBaseNeg2();
  return 0;
}
