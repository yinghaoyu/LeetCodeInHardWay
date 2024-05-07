#include <string>
#include <vector>

using namespace std;

// 数位 dp
// @sa https://www.bilibili.com/video/BV1cC4y1Q7r3/
// TODO: 简化代码，减少运行时间
class Solution
{
 private:
  static const int MOD = 1e9 + 7;
  static const int MAXN = 23;
  static const int MAXM = 401;

 public:
  void clear(vector<vector<vector<int>>>& dp)
  {
    for (int i = 0; i < MAXN; i++)
    {
      for (int j = 0; j < MAXM; j++)
      {
        dp[i][j][0] = -1;
        dp[i][j][1] = -1;
      }
    }
  }

  bool check(string& num, int min, int max)
  {
    int sum = 0;
    for (char cha : num)
    {
      sum += cha - '0';
    }
    return sum >= min && sum <= max;
  }

  int count(string num1, string num2, int min_sum, int max_sum)
  {
    vector<vector<vector<int>>> dp(MAXN, vector<vector<int>>(MAXM, vector<int>(2, -1)));

    int p1 = f(0, 0, 0, num2, min_sum, max_sum, dp);
    clear(dp);
    int p2 = f(0, 0, 0, num1, min_sum, max_sum, dp);
    return (p1 - p2 + MOD + check(num1, min_sum, max_sum)) % MOD;
  }

  // 注意：
  // 数字，string num
  // 数字长度，int len
  // 累加和最小要求，int min
  // 累加和最大要求，int max
  // 递归含义：
  // 从num的高位出发，当前来到i位上
  // 之前决定的数字累加和是sum
  // 之前的决定已经比num小，后续可以自由选择数字，那么free == 1
  // 之前的决定和num一样，后续不可以自由选择数字，那么free == 0
  // 返回有多少种可能性
  int f(int i, int sum, int free, string& num, int min, int max, vector<vector<vector<int>>>& dp)
  {
    if (sum > max)
    {
      return 0;
    }
    if (sum + (num.length() - i) * 9 < min)
    {
      return 0;
    }
    if (i == num.length())
    {
      return 1;
    }
    if (dp[i][sum][free] != -1)
    {
      return dp[i][sum][free];
    }
    // cur : num当前位的数字
    int cur = num[i] - '0';
    int ans = 0;
    if (free == 0)
    {
      // 还不能自由选择
      for (int pick = 0; pick < cur; pick++)
      {
        ans = (ans + f(i + 1, sum + pick, 1, num, min, max, dp)) % MOD;
      }
      ans = (ans + f(i + 1, sum + cur, 0, num, min, max, dp)) % MOD;
    }
    else
    {
      // 可以自由选择
      for (int pick = 0; pick <= 9; pick++)
      {
        ans = (ans + f(i + 1, sum + pick, 1, num, min, max, dp)) % MOD;
      }
    }
    dp[i][sum][free] = ans;
    return ans;
  }
};
