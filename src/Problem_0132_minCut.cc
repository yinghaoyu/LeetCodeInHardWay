#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  int minCut(string s)
  {
    int n = s.length();
    // 预处理
    // dp[i][j]表示s[i...j]是否为回文串
    vector<vector<int>> dp(n, vector<int>(n, true));
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = i + 1; j < n; j++)
      {
        dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
      }
    }

    // f[i] 表示字符串的前缀 s[0..i] 的最少分割次数
    vector<int> f(n, INT32_MAX);
    for (int i = 0; i < n; i++)
    {
      if (dp[0][i])
      {
        // 如果本身就是回文串，则不需要分割
        f[i] = 0;
      }
      else
      {
        // 在s[0...i-1]上尝试分割
        for (int j = 0; j < i; j++)
        {
          if (dp[j + 1][i])
          {
            // 保证 s[j+1...i]是回文串，那么f[i]可以从f[j] + 1得来
            f[i] = std::min(f[i], f[j] + 1);
          }
        }
      }
    }
    return f[n - 1];
  }
};
