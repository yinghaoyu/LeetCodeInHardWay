#include <string>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  // 暴力尝试，4个参数
  bool isScramble(string s1, string s2)
  {
    int n = s1.length();
    return f1(s1, 0, n - 1, s2, 0, n - 1);
  }

  // s1[l1....r1]
  // s2[l2....r2]
  // 保证l1....r1与l2....r2
  // 是不是扰乱串的关系
  bool f1(string& s1, int l1, int r1, string& s2, int l2, int r2)
  {
    if (l1 == r1)
    {
      // s1[l1..r1]
      // s2[l2..r2]
      return s1[l1] == s2[l2];
    }
    // s1[l1..i][i+1....r1]
    // s2[l2..j][j+1....r2]
    // 不交错去讨论扰乱关系
    for (int i = l1, j = l2; i < r1; i++, j++)
    {
      if (f1(s1, l1, i, s2, l2, j) && f1(s1, i + 1, r1, s2, j + 1, r2))
      {
        return true;
      }
    }
    // 交错去讨论扰乱关系
    // s1[l1..........i][i+1...r1]
    // s2[l2...j-1][j..........r2]
    for (int i = l1, j = r2; i < r1; i++, j--)
    {
      if (f1(s1, l1, i, s2, j, r2) && f1(s1, i + 1, r1, s2, l2, j - 1))
      {
        return true;
      }
    }
    return false;
  }

  // 暴力尝试，3个参数
  bool isScramble2(string s1, string s2)
  {
    int n = s1.length();
    return f2(s1, s2, 0, 0, n);
  }

  bool f2(string& s1, string& s2, int l1, int l2, int len)
  {
    if (len == 1)
    {
      return s1[l1] == s2[l2];
    }
    // s1[l1.......]  len
    // s2[l2.......]  len
    // 左 : k个   右: len - k 个
    for (int k = 1; k < len; k++)
    {
      if (f2(s1, s2, l1, l2, k) && f2(s1, s2, l1 + k, l2 + k, len - k))
      {
        return true;
      }
    }
    // 交错！
    for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
    {
      if (f2(s1, s2, l1, j, k) && f2(s1, s2, i, l2, len - k))
      {
        return true;
      }
    }
    return false;
  }

  int isScramble3(string s1, string s2)
  {
    int n = s1.length();
    // dp[l1][l2][len] : int 0 -> 没展开过
    // dp[l1][l2][len] : int -1 -> 展开过，返回的结果是false
    // dp[l1][l2][len] : int 1 -> 展开过，返回的结果是true
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(n + 1)));
    return f3(s1, s2, 0, 0, n, dp);
  }

  bool f3(string& s1, string& s2, int l1, int l2, int len, vector<vector<vector<int>>>& dp)
  {
    if (len == 1)
    {
      return s1[l1] == s2[l2];
    }
    if (dp[l1][l2][len] != 0)
    {
      return dp[l1][l2][len] == 1;
    }
    bool ans = false;
    for (int k = 1; k < len; k++)
    {
      if (f3(s1, s2, l1, l2, k, dp) && f3(s1, s2, l1 + k, l2 + k, len - k, dp))
      {
        ans = true;
        break;
      }
    }
    if (!ans)
    {
      for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
      {
        if (f3(s1, s2, l1, j, k, dp) && f3(s1, s2, i, l2, len - k, dp))
        {
          ans = true;
          break;
        }
      }
    }
    dp[l1][l2][len] = ans ? 1 : -1;
    return ans;
  }

  bool isScramble4(string s1, string s2)
  {
    int n = s1.length();
    vector<vector<vector<bool>>> dp(n, vector<vector<bool>>(n, vector<bool>(n + 1)));
    // 填写len=1层，所有的格子
    for (int l1 = 0; l1 < n; l1++)
    {
      for (int l2 = 0; l2 < n; l2++)
      {
        dp[l1][l2][1] = s1[l1] == s2[l2];
      }
    }
    for (int len = 2; len <= n; len++)
    {
      // 注意如下的边界条件 : l1 <= n - len l2 <= n - len
      for (int l1 = 0; l1 <= n - len; l1++)
      {
        for (int l2 = 0; l2 <= n - len; l2++)
        {
          for (int k = 1; k < len; k++)
          {
            if (dp[l1][l2][k] && dp[l1 + k][l2 + k][len - k])
            {
              dp[l1][l2][len] = true;
              break;
            }
          }
          if (!dp[l1][l2][len])
          {
            for (int i = l1 + 1, j = l2 + len - 1, k = 1; k < len; i++, j--, k++)
            {
              if (dp[l1][j][k] && dp[i][l2][len - k])
              {
                dp[l1][l2][len] = true;
                break;
              }
            }
          }
        }
      }
    }
    return dp[0][0][n];
  }
};
