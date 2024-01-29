#include <string>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 private:
  std::pair<int, int> zerosAndOnes(string& str)
  {
    int zeros = 0;
    int ones = 0;
    for (int i = 0; i < str.length(); i++)
    {
      if (str[i] == '0')
      {
        zeros++;
      }
      else
      {
        ones++;
      }
    }
    return {zeros, ones};
  }

 public:
  int findMaxForm1(vector<string>& strs, int m, int n) { return f1(strs, 0, m, n); }

  int f1(vector<string>& strs, int i, int z, int o)
  {
    if (i == strs.size())
    {
      // 没有字符串了
      return 0;
    }
    // 不使用当前的str[i]字符串
    int p1 = f1(strs, i + 1, z, o);
    // 使用当前的strs[i]字符串
    int p2 = 0;
    auto [zeros, ones] = zerosAndOnes(strs[i]);
    if (zeros <= z && ones <= o)
    {
      p2 = 1 + f1(strs, i + 1, z - zeros, o - ones);
    }
    return std::max(p1, p2);
  }

  // 记忆化搜素
  int findMaxForm2(vector<string>& strs, int m, int n)
  {
    vector<vector<vector<int>>> dp(strs.size(), vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
    return f2(strs, 0, m, n, dp);
  }

  int f2(vector<string>& strs, int i, int z, int o, vector<vector<vector<int>>>& dp)
  {
    if (i == strs.size())
    {
      return 0;
    }
    if (dp[i][z][o] != -1)
    {
      return dp[i][z][o];
    }
    int p1 = f2(strs, i + 1, z, o, dp);
    int p2 = 0;
    auto [zeros, ones] = zerosAndOnes(strs[i]);
    if (zeros <= z && ones <= o)
    {
      p2 = 1 + f2(strs, i + 1, z - zeros, o - ones, dp);
    }
    int ans = std::max(p1, p2);
    dp[i][z][o] = ans;
    return ans;
  }

  // 动态规划
  int findMaxForm3(vector<string>& strs, int m, int n)
  {
    int len = strs.size();
    vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
    for (int i = len - 1; i >= 0; i--)
    {
      auto [zeros, ones] = zerosAndOnes(strs[i]);
      for (int z = 0, p1, p2; z <= m; z++)
      {
        for (int o = 0; o <= n; o++)
        {
          p1 = dp[i + 1][z][o];
          p2 = 0;
          if (zeros <= z && ones <= o)
          {
            p2 = 1 + dp[i + 1][z - zeros][o - ones];
          }
          dp[i][z][o] = std::max(p1, p2);
        }
      }
    }
    return dp[0][m][n];
  }

  // 空间优化
  int findMaxForm4(vector<string>& strs, int m, int n)
  {
    // 代表i == len
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (auto& s : strs)
    {
      // 每个字符串逐渐遍历即可
      // 更新每一层的表
      // 和之前的遍历没有区别
      auto [zeros, ones] = zerosAndOnes(s);
      for (int z = m; z >= zeros; z--)
      {
        for (int o = n; o >= ones; o--)
        {
          dp[z][o] = std::max(dp[z][o], 1 + dp[z - zeros][o - ones]);
        }
      }
    }
    return dp[m][n];
  }
};
