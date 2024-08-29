#include <cstdint>
#include <string>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 记忆化搜索
  int minimumSubstringsInPartition1(string s)
  {
    int n = s.length();
    // dp[i] 的含义为 s[0...i]内，最少能分割多少个平衡子串
    vector<int> dp(n, -1);
    return dfs(n - 1, s, dp);
  }

  int dfs(int i, string& s, vector<int>& dp)
  {
    if (i < 0)
    {
      return 0;
    }
    if (dp[i] != -1)
    {
      return dp[i];
    }
    int ans = INT32_MAX;
    vector<int> cnt(26);
    // 不同字符种类
    int k = 0;
    // 字符计数的最大值
    int max = 0;
    for (int j = i; j >= 0; j--)
    {
      // 新字符加入
      k += cnt[s[j] - 'a']++ == 0;
      // 字符计数最大值
      max = std::max(max, cnt[s[j] - 'a']);
      // 检查是否每个字符的计数都一样
      if (i - j + 1 == k * max)
      {
        // 如果 s[i...j] 是平衡字符串，那么讨论子问题s[0...j-1]
        ans = std::min(ans, dfs(j - 1, s, dp) + 1);
      }
    }
    dp[i] = ans;
    return ans;
  }

  // 动态规划
  int minimumSubstringsInPartition2(string s)
  {
    int n = s.length();
    vector<int> dp(n + 1, INT32_MAX);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
    {
      vector<int> cnt(26);
      int k = 0;
      int max = 0;
      for (int j = i; j >= 0; j--)
      {
        k += cnt[s[j] - 'a']++ == 0;
        max = std::max(max, cnt[s[j] - 'a']);
        if (i - j + 1 == k * max)
        {
          dp[i + 1] = std::min(dp[i + 1], dp[j] + 1);
        }
      }
    }
    return dp[n];
  }
};
