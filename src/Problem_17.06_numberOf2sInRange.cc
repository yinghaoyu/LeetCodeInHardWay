#include <string>
#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/number-of-2s-in-range-lcci/solutions/1750395/by-endlesscheng-x4mf/
class Solution
{
 public:
  // 数位DP、树形DP
  int numberOf2sInRange(int n)
  {
    string s = std::to_string(n);
    int m = s.length();
    vector<vector<int>> dp(m, vector<int>(m, -1));
    return f(0, 0, true, s, dp);
  }

  // i 表示遍历的位置
  // cnt 表示碰到 2 的次数
  // limited 表示是否受限
  // 返回总共遇到 2 的次数
  int f(int i, int cnt, bool limited, string& s, vector<vector<int>>& dp)
  {
    if (i == s.length())
    {
      return cnt;
    }
    if (!limited && dp[i][cnt] != -1)
    {
      // TODO: 想想这里为什么 !limited 才去记忆化?
      return dp[i][cnt];
    }
    int ans = 0;
    for (int j = 0, k = limited ? s[i] - '0' : 9; j <= k; j++)
    {
      ans += f(i + 1, cnt + (j == 2), limited && j == k, s, dp);
    }
    if (!limited)
    {
      dp[i][cnt] = ans;
    }
    return ans;
  }
};
