#include <string>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/omKAoA/
// Problem_0132_minCut.cc
class Solution
{
 public:
  int minCut(string s)
  {
    int n = s.length();
    vector<vector<bool>> dp(n, vector<bool>(n, true));
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = i + 1; j < n; j++)
      {
        dp[i][j] = (s[i] == s[j]) && dp[i + 1][j - 1];
      }
    }
    vector<int> f(n, INT32_MAX);
    for (int i = 0; i < n; i++)
    {
      if (dp[0][i])
      {
        f[i] = 0;
      }
      else
      {
        for (int j = i - 1; j >= 0; j--)
        {
          if (dp[j + 1][i])
          {
            f[i] = std::min(f[i], f[j] + 1);
          }
        }
      }
    }
    return f[n - 1];
  }
};
