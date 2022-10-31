#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int magicalString(int n)
  {
    // 122
    if (n < 4)
    {
      return 1;
    }
    string s(n, '0');
    s[0] = '1';
    s[1] = '2';
    s[2] = '2';
    int ans = 1;
    int i = 2;  // 当前构造字符的数量
    int j = 3;  // 当前构造字符的位置
    while (j < n)
    {
      int size = s[i] - '0';
      int num = 3 - (s[j - 1] - '0');
      while (size > 0 && j < n)
      {
        s[j] = num + '0';
        if (num == 1)
        {
          ans++;
        }
        j++;
        size--;
      }
      i++;
    }
    return ans;
  }
};

void testMagicalString()
{
  Solution s;
  EXPECT_EQ_INT(3, s.magicalString(6));
  EXPECT_EQ_INT(1, s.magicalString(1));
  EXPECT_SUMMARY;
}

int main()
{
  testMagicalString();
  return 0;
}
