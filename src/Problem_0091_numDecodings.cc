#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递归
  int process(string &s, int cur)
  {
    if (cur == s.length())
    {
      return 1;
    }
    if (s[cur] == '0')
    {
      return 0;
    }
    int ways = process(s, cur + 1);
    if (cur + 1 == s.length())
    {
      return ways;
    }
    int num = (s[cur] - '0') * 10 + s[cur + 1] - '0';
    if (num <= 26)
    {
      ways += process(s, cur + 2);
    }
    return ways;
  }

  int numDecodings(string s)
  {
    if (s.length() == 0)
    {
      return 0;
    }
    return process(s, 0);
  }

  // 递归改dp
  int dp(string s)
  {
    int n = s.length();
    vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
      if (s[i] != '0')
      {
        dp[i] += dp[i + 1];
        if (i + 1 < n)
        {
          int num = (s[i] - '0') * 10 + s[i + 1] - '0';
          dp[i] += num <= 26 ? dp[i + 2] : 0;
        }
      }
    }
    return dp[0];
  }
};

void testNumDecodings()
{
  Solution s;
  EXPECT_EQ_INT(2, s.numDecodings("12"));
  EXPECT_EQ_INT(3, s.numDecodings("226"));
  EXPECT_EQ_INT(0, s.numDecodings("06"));
  EXPECT_EQ_INT(2, s.dp("12"));
  EXPECT_EQ_INT(3, s.dp("226"));
  EXPECT_EQ_INT(0, s.dp("06"));
  EXPECT_SUMMARY;
}

int main()
{
  testNumDecodings();
  return 0;
}
