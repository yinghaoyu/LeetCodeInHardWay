#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int myAtoi(string s)
  {
    int ret = 0, i, flag = 0;
    for (i = 0; s[i] == ' '; i++)
      ;               // 过滤空格
    if (s[i] == '-')  // 判断正负
    {
      flag = 1;
      i++;
    }
    else if (s[i] == '+')
    {
      i++;
    }
    for (; s[i] >= '0' && s[i] <= '9'; i++)  // 只处理数字
    {
      if (ret > (0x7fffffff - (s[i] - '0')) / 10)  // 溢出处理
      {
        if (flag)
        {
          return 1 << 31;  // 负溢出返回- 2^32
        }
        else
        {
          return ~(1 << 31);  // 正溢出返回2^32 - 1
        }
      }
      ret *= 10;
      ret += (s[i] - '0');
    }
    if (flag)
    {
      ret = ~ret + 1;  // 取负
    }
    return ret;
  }
};

void testMyAtoi()
{
  Solution s;
  EXPECT_EQ_INT(42, s.myAtoi("42"));
  EXPECT_EQ_INT(-42, s.myAtoi("     -42"));
  EXPECT_EQ_INT(4193, s.myAtoi("4193 with words"));
  EXPECT_EQ_INT(0, s.myAtoi("words and 987"));
  EXPECT_EQ_INT(~(1 << 31), s.myAtoi("2147483648"));
  EXPECT_EQ_INT(1 << 31, s.myAtoi("-2147483649"));
  EXPECT_SUMMARY;
}

int main()
{
  testMyAtoi();
  return 0;
}
