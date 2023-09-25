#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minFlipsMonoIncr(string s)
  {
    int n = s.length();
    // dp[i][0] 和 dp[i][1] 分别表示下标 i 处的字符为 0 和 1 的情况下使得 s[0..i] 单调递增的最小翻转次数
    vector<vector<int>> dp(n, vector<int>(2));
    // base case
    // s[i] 表示实际字符，dp[i][j]，其中 j 表示预期字符
    // 当只有 0 位置字符时，预期字符与实际字符不相等需要翻转一次
    dp[0][0] = s[0] == '0' ? 0 : 1;
    dp[0][1] = s[0] == '1' ? 0 : 1;
    for (int i = 1; i < n; i++)
    {
      if (s[i] == '1')
      {
        // 当前字符是 `1`，要变成预期字符 `0` 的话，需要翻转 1 次，因此 +1
        // 同时需要前面是 `0`
        dp[i][0] = dp[i - 1][0] + 1;
        // 已经是`1`，不需翻转，同时前面既可以是 `0`，也可以是 `1`
        dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]);
      }
      else
      {
        // 已经是 `0`，不需要翻转，同时前面必须是`0`
        dp[i][0] = dp[i - 1][0];
        // 当前位置是 `0`,变成 `1` 需要翻转 1 次，
        dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + 1;
      }
    }
    return std::min(dp[n - 1][0], dp[n - 1][1]);
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(1, s.minFlipsMonoIncr("00110"));
  EXPECT_EQ_INT(2, s.minFlipsMonoIncr("010110"));
  EXPECT_EQ_INT(2, s.minFlipsMonoIncr("00011000"));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
