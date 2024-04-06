#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int longestCommonSubsequence1(string s1, string s2)
  {
    int n = s1.length();
    int m = s2.length();
    return f1(s1, s2, n - 1, m - 1);
  }

  // s1[0....i1]与s2[0....i2]最长公共子序列长度
  int f1(string& s1, string& s2, int i1, int i2)
  {
    if (i1 < 0 || i2 < 0)
    {
      return 0;
    }
    int p1 = f1(s1, s2, i1 - 1, i2 - 1);
    int p2 = f1(s1, s2, i1 - 1, i2);
    int p3 = f1(s1, s2, i1, i2 - 1);
    int p4 = s1[i1] == s2[i2] ? (p1 + 1) : 0;
    return std::max({p1, p2, p3, p4});
  }

  // 为了避免很多边界讨论
  // 很多时候往往不用下标来定义尝试，而是用长度来定义尝试
  // 因为长度最短是0，而下标越界的话讨论起来就比较麻烦
  int longestCommonSubsequence2(string s1, string s2)
  {
    int n = s1.length();
    int m = s2.length();
    return f2(s1, s2, n, m);
  }

  // s1[前缀长度为len1]对应s2[前缀长度为len2]
  // 最长公共子序列长度
  int f2(string& s1, string& s2, int len1, int len2)
  {
    if (len1 == 0 || len2 == 0)
    {
      return 0;
    }
    int ans = 0;
    if (s1[len1 - 1] == s2[len2 - 1])
    {
      ans = f2(s1, s2, len1 - 1, len2 - 1) + 1;
    }
    else
    {
      // 优化项: 为什么这里不考虑 f2(s1, s2, len1 - 1, len2 - 1) ?
      // 因为 s1 和 s2 长度都变小了，最后一定都小于 s1 或者 s2 只有一个字符串变小的情况
      ans = std::max(f2(s1, s2, len1 - 1, len2), f2(s1, s2, len1, len2 - 1));
    }
    return ans;
  }

  // 记忆化搜索
  int longestCommonSubsequence3(string s1, string s2)
  {
    int n = s1.length();
    int m = s2.length();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
    return f3(s1, s2, n, m, dp);
  }

  int f3(string& s1, string& s2, int len1, int len2, vector<vector<int>>& dp)
  {
    if (len1 == 0 || len2 == 0)
    {
      return 0;
    }
    if (dp[len1][len2] != -1)
    {
      return dp[len1][len2];
    }
    int ans;
    if (s1[len1 - 1] == s2[len2 - 1])
    {
      ans = f3(s1, s2, len1 - 1, len2 - 1, dp) + 1;
    }
    else
    {
      ans = std::max(f3(s1, s2, len1 - 1, len2, dp), f3(s1, s2, len1, len2 - 1, dp));
    }
    dp[len1][len2] = ans;
    return ans;
  }

  // 严格位置依赖的动态规划
  int longestCommonSubsequence4(string s1, string s2)
  {
    int n = s1.length();
    int m = s2.length();
    // i j 分别表示 s1 s2 长度
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= m; j++)
      {
        if (s1[i - 1] == s2[j - 1])
        {
          dp[i][j] = 1 + dp[i - 1][j - 1];
        }
        else
        {
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
      }
    }
    return dp[n][m];
  }

  // @sa https://www.bilibili.com/video/BV1WQ4y1W7d1/
  // 严格位置依赖的动态规划 + 空间压缩
  int longestCommonSubsequence5(string s1, string s2)
  {
    // 准备一维数组时，看谁更短
    if (s1.length() > s2.length())
    {
      std::swap(s1, s2);
    }
    int n = s1.length();
    int m = s2.length();
    vector<int> dp(m + 1);
    // i j 分别表示 s1 s2 长度
    for (int i = 1; i <= n; i++)
    {
      int leftUp = 0, backup;
      for (int j = 1; j <= m; j++)
      {
        backup = dp[j];
        if (s1[i - 1] == s2[j - 1])
        {
          dp[j] = 1 + leftUp;
        }
        else
        {
          dp[j] = std::max(dp[j], dp[j - 1]);
        }
        leftUp = backup;
      }
    }
    return dp[m];
  }
};
