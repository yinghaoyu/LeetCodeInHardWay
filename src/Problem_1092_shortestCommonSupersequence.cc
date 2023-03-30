#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// 参考链接：https://leetcode.cn/problems/shortest-common-supersequence/solution/cong-di-gui-dao-di-tui-jiao-ni-yi-bu-bu-auy8z/
// TODO: figure it out
class Solution
{
 public:
  // 暴力递归
  string process(string &s1, string &s2)
  {
    if (s1.empty())
    {
      // base case
      return s2;
    }
    if (s2.empty())
    {
      // base case
      return s1;
    }
    string x = s1.substr(0, s1.length() - 1);
    string y = s2.substr(0, s2.length() - 1);
    if (s1.back() == s2.back())
    {
      return process(x, y) + s1.back();
    }
    string p1 = process(x, s2);
    string p2 = process(s1, y);
    if (p1.length() < p2.length())
    {
      return p1 + s1.back();
    }
    else
    {
      return p2 + s2.back();
    }
  }

  string shortestCommonSupersequence1(string str1, string str2) { return process(str1, str2); }

  string shortestCommonSupersequence3(string str1, string str2)
  {
    int N = str1.length();
    int M = str2.length();
    // dp[i][j] 表示 s 的前 i 个字母和 t 的前 j 个字母的最短公共超序列的长度
    vector<vector<int>> dp(N + 1, vector<int>(M + 1));
    for (int i = 0; i <= N; i++)
    {
      dp[i][0] = i;
    }
    for (int j = 0; j <= M; j++)
    {
      dp[0][j] = j;
    }
    for (int i = 1; i <= N; i++)
    {
      for (int j = 1; j <= M; j++)
      {
        // 第 i 个字母下标为 i - 1，第 j 个字母的下标为 j - 1
        if (str1[i - 1] == str2[j - 1])
        {
          dp[i][j] = dp[i - 1][j - 1] + 1;
        }
        else
        {
          dp[i][j] = std::min(dp[i - 1][j], dp[i][j - 1]) + 1;
        }
      }
    }
    int i = N;
    int j = M;
    string ans;
    // 因为只知道终点，不知道起点，所以需要逆向还原
    while (i > 0 || j > 0)
    {
      if (i == 0)
      {
        ans += str2[--j];
      }
      else if (j == 0)
      {
        ans += str1[--i];
      }
      else
      {
        if (dp[i][j] == dp[i - 1][j] + 1)
        {
          ans += str1[--i];
        }
        else if (dp[i][j] == dp[i][j - 1] + 1)
        {
          ans += str2[--j];
        }
        else
        {
          ans += str1[--i], --j;
        }
      }
    }
    std::reverse(ans.begin(), ans.end());
    return ans;
  }
};
