#include <iostream>
#include <string>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  string getDigits(string str)
  {
    string ans;
    for (int i = 0; i < str.length(); i++)
    {
      if (str[i] != ' ' && str[i] != '-')
      {
        ans.push_back(str[i]);
      }
    }
    return ans;
  }

  string reformatNumber(string number)
  {
    string digits = getDigits(number);
    string ans;
    int N = digits.length();
    bool diff = N % 3 == 1 ? true : false;
    for (int i = 0; i < N; i++)
    {
      if (i != 0 && i % 3 == 0)
      {
        // 除0位置，每3个字符加-
        ans.push_back('-');
      }
      if (diff && N - i == 4)
      {
        // 特殊情况
        ans += digits.substr(N - 4, 2) + "-" + digits.substr(N - 2, 2);
        break;
      }
      ans.push_back(digits[i]);
    }
    return ans;
  }
};

bool isEqualString(string s1, string s2)
{
  if (s1.length() != s2.length())
  {
    return false;
  }
  for (int i = 0; i < s1.length(); i++)
  {
    if (s1[i] != s2[i])
    {
      return false;
    }
  }
  return true;
}

void testReformatNumber()
{
  Solution s;
  EXPECT_TRUE(isEqualString("123-456", s.reformatNumber("1 - 23 - 45 6")));
  EXPECT_TRUE(isEqualString("123-45-67", s.reformatNumber("123 4-567")));
  EXPECT_TRUE(isEqualString("123-456-78", s.reformatNumber("123 4-5678")));
  EXPECT_SUMMARY;
}

int main()
{
  testReformatNumber();
  return 0;
}
