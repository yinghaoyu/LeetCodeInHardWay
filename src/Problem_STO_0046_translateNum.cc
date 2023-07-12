#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 递归
  int process(string &str, int index)
  {
    if (index == str.length())
    {
      return 1;
    }
    int p1 = 0;
    if (index + 1 < str.length())
    {
      // 注意，题设 `a` 是从 0 开始，不是从 `1` 开始
      // 也就是说 109 的 09 是不能合并的 !!!
      int num = (str[index] - '0') * 10 + (str[index+1] -'0');
      p1 = num > 9 && num < 26 ? process(str, index + 2) : 0;
    }
    int p2 = process(str, index + 1);

    return p1 + p2;
  }

  int translateNum(int num)
  {
    string str = std::to_string(num);
    return process(str, 0);
  }

  // 递归改动态规划
  int dp(int num)
  {
    string str = std::to_string(num);
    int n = str.length();
    vector<int> dp(n + 1);
    dp[n] = 1;
    for (int i = n - 1; i >= 0; i--)
    {
      dp[i] = dp[i + 1];
      if (i + 2 <= n)
      {
        int num = (str[i] - '0') * 10 + (str[i+1] -'0');
        dp[i] += num > 9 && num < 26 ? dp[i + 2] : 0;
      }
    }
    return dp[0];
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(5, s.translateNum(12258));
  EXPECT_EQ_INT(2, s.translateNum(25));
  EXPECT_EQ_INT(5, s.dp(12258));
  EXPECT_EQ_INT(2, s.dp(25));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
