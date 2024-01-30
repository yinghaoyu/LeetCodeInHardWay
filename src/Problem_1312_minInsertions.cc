#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 暴力尝试
  int minInsertions1(string s)
  {
    int n = s.length();
    return f1(s, 0, n - 1);
  }

  // s[l....r]这个范围上的字符串，整体都变成回文串
  // 返回至少插入几个字符
  int f1(string& s, int l, int r)
  {
    // l <= r
    if (l == r)
    {
      return 0;
    }
    if (l + 1 == r)
    {
      return s[l] == s[r] ? 0 : 1;
    }
    // l...r不只两个字符
    if (s[l] == s[r])
    {
      return f1(s, l + 1, r - 1);
    }
    else
    {
      return std::min(f1(s, l, r - 1), f1(s, l + 1, r)) + 1;
    }
  }

  // 记忆化搜索
  int minInsertions2(string s)
  {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return f2(s, 0, n - 1, dp);
  }

  int f2(string& s, int l, int r, vector<vector<int>>& dp)
  {
    if (dp[l][r] != -1)
    {
      return dp[l][r];
    }
    int ans = 0;
    if (l == r)
    {
      ans = 0;
    }
    else if (l + 1 == r)
    {
      ans = s[l] == s[l + 1] ? 0 : 1;
    }
    else
    {
      if (s[l] == s[r])
      {
        ans = f2(s, l + 1, r - 1, dp);
      }
      else
      {
        ans = std::min(f2(s, l, r - 1, dp), f2(s, l + 1, r, dp)) + 1;
      }
    }
    dp[l][r] = ans;
    return ans;
  }

  // 动态规划
  int minInsertions3(string s)
  {
    int n = s.length();
    vector<vector<int>> dp(n, vector<int>(n));
    for (int l = 0; l < n - 1; l++)
    {
      dp[l][l + 1] = s[l] == s[l + 1] ? 0 : 1;
    }
    for (int l = n - 3; l >= 0; l--)
    {
      for (int r = l + 2; r < n; r++)
      {
        if (s[l] == s[r])
        {
          dp[l][r] = dp[l + 1][r - 1];
        }
        else
        {
          dp[l][r] = std::min(dp[l][r - 1], dp[l + 1][r]) + 1;
        }
      }
    }
    return dp[0][n - 1];
  }

  // 空间压缩
  int minInsertions4(string s)
  {
    int n = s.length();
    if (n < 2)
    {
      return 0;
    }
    vector<int> dp(n);
    dp[n - 1] = s[n - 2] == s[n - 1] ? 0 : 1;
    for (int l = n - 3, leftDown, backUp; l >= 0; l--)
    {
      leftDown = dp[l + 1];
      dp[l + 1] = s[l] == s[l + 1] ? 0 : 1;
      for (int r = l + 2; r < n; r++)
      {
        backUp = dp[r];
        if (s[l] == s[r])
        {
          dp[r] = leftDown;
        }
        else
        {
          dp[r] = std::min(dp[r - 1], dp[r]) + 1;
        }
        leftDown = backUp;
      }
    }
    return dp[n - 1];
  }
};
