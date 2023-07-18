#include <iostream>
#include <vector>

using namespace std;

// same as leetcode 0647
// https://leetcode-cn.com/problems/palindromic-substrings/
// see at Problem_0647_countSubstrings.cc
class Solution
{
 public:
  // TODO: use Manacher
  int countSubstrings(string s)
  {
    int n = s.length();
    // dp[i][j]表示在s[i...j]是否回文
    vector<vector<bool>> dp(n, vector<bool>(n));
    for (int i = 0; i < n; i++)
    {
      // 单字符当然是回文串
      dp[i][i] = true;
    }
    // 所有单个字符一定为回文串
    int ans = n;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (s[i] != s[j])
        {
          continue;
        }
        // s[i] == s[j]
        // j == i + 1 只有两个字符
        // 两个字符以上，取决于dp[i+1][j-1]
        if (j == i + 1 || dp[i + 1][j - 1])
        {
          dp[i][j] = true;
          ans++;
        }
      }
    }
    return ans;
  }
};
