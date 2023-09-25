#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/flip-string-to-monotone-increasing/
// @sa Problem_0926_minFlipsMonoIncr.cc

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
    dp[0][0] = s[0] != '0';
    dp[0][1] = s[0] != '1';
    for (int i = 1; i < n; i++)
    {
      // TODO: 空间优化
      dp[i][0] = dp[i - 1][0] + (s[i] != '0');
      dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][1]) + (s[i] != '1');
    }
    return std::min(dp[n - 1][0], dp[n - 1][1]);
  }
};
