#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 最长回文子序列问题可以转化成最长公共子序列问题
  // 不过这里讲述区间动态规划的思路
  int longestPalindromeSubseq(string s)
  {
    int n = s.length();
    return f1(s, 0, n - 1);
  }

  // s[l...r]最长回文子序列长度
  // l <= r
  int f1(string& s, int l, int r)
  {
    if (l == r)
    {
      return 1;
    }
    if (l + 1 == r)
    {
      return s[l] == s[r] ? 2 : 1;
    }
    if (s[l] == s[r])
    {
      return 2 + f1(s, l + 1, r - 1);
    }
    else
    {
      return std::max(f1(s, l + 1, r), f1(s, l, r - 1));
    }
  }

  // 记忆化搜索
  int longestPalindromeSubseq2(string s)
  {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n));
    return f2(s, 0, n - 1, dp);
  }

  int f2(string& s, int l, int r, vector<vector<int>>& dp)
  {
    if (l == r)
    {
      return 1;
    }
    if (l + 1 == r)
    {
      return s[l] == s[r] ? 2 : 1;
    }
    if (dp[l][r] != 0)
    {
      return dp[l][r];
    }
    int ans;
    if (s[l] == s[r])
    {
      ans = 2 + f2(s, l + 1, r - 1, dp);
    }
    else
    {
      ans = std::max(f2(s, l + 1, r, dp), f2(s, l, r - 1, dp));
    }
    dp[l][r] = ans;
    return ans;
  }

  // 动态规划
  int longestPalindromeSubseq3(string s)
  {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int l = n - 1; l >= 0; l--)
    {
      dp[l][l] = 1;
      if (l + 1 < n)
      {
        dp[l][l + 1] = s[l] == s[l + 1] ? 2 : 1;
      }
      for (int r = l + 2; r < n; r++)
      {
        if (s[l] == s[r])
        {
          dp[l][r] = 2 + dp[l + 1][r - 1];
        }
        else
        {
          dp[l][r] = std::max(dp[l + 1][r], dp[l][r - 1]);
        }
      }
    }
    return dp[0][n - 1];
  }

  // 动态规划空间优化
  int longestPalindromeSubseq4(string s)
  {
    int n = s.length();
    vector<int> dp(n);
    for (int l = n - 1, leftDown = 0, backup; l >= 0; l--)
    {
      // dp[l] : 想象中的dp[l][l]
      dp[l] = 1;
      if (l + 1 < n)
      {
        leftDown = dp[l + 1];
        // dp[l+1] : 想象中的dp[l][l+1]
        dp[l + 1] = s[l] == s[l + 1] ? 2 : 1;
      }
      for (int r = l + 2; r < n; r++)
      {
        backup = dp[r];
        if (s[l] == s[r])
        {
          dp[r] = 2 + leftDown;
        }
        else
        {
          dp[r] = std::max(dp[r], dp[r - 1]);
        }
        leftDown = backup;
      }
    }
    return dp[n - 1];
  }
};
