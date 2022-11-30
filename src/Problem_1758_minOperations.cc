#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minOperations(string s)
  {
    int ans = 0;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      char c = s[i];
      if (c != ('0' + i % 2))
      {
        ans++;
      }
    }
    // 另一个交替串的次数s.size() - cnt怎么得来的？
    // 因为假设的两种情况是完全相反的。
    // 举例来说，1111变成1010和变成0101
    // 第一种情况中不需要变的数 = 第二种情况中需要变的数
    // 第一种情况中需要变的数 + 第一种情况中不需要变的数 = 字符串总长度
    // 故推得第一种情况中需要变的数 + 第二种情况中需要变的数 = 字符串总长度
    return std::min(ans, n - ans);
  }
};

void testMinOperations()
{
  Solution s;
  EXPECT_EQ_INT(1, s.minOperations("0100"));
  EXPECT_EQ_INT(0, s.minOperations("10"));
  EXPECT_EQ_INT(2, s.minOperations("1111"));
  EXPECT_SUMMARY;
}

int main()
{
  testMinOperations();
  return 0;
}
