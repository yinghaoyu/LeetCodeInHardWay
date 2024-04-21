#include <string>
#include <vector>

using namespace std;

// 区间dp
// @sa https://www.bilibili.com/video/BV1NQ4y1b7Uo/
class Solution
{
 public:
  // 记忆化搜索
  int countEval1(string s, int result)
  {
    int n = s.length();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n));
    vector<int> ft = func(s, 0, n - 1, dp);
    return ft[result];
  }

  // s[l...r]是表达式的一部分，且一定符合范式
  // 0/1  逻  0/1   逻       0/1
  //  l  l+1  l+2  l+3........r
  // s[l...r]  0 : ?
  //           1 : ?
  // ans : int[2] ans[0] = false方法数 ans[0] = true方法数
  vector<int> func(string& s, int l, int r, vector<vector<vector<int>>>& dp)
  {
    if (!dp[l][r].empty())
    {
      return dp[l][r];
    }
    int f = 0;
    int t = 0;
    if (l == r)
    {
      // 只剩一个字符，0/1
      f = s[l] == '0' ? 1 : 0;
      t = s[l] == '1' ? 1 : 0;
    }
    else
    {
      vector<int> tmp;
      for (int k = l + 1, a, b, c, d; k < r; k += 2)
      {
        // l ... r
        // 枚举每一个逻辑符号最后执行 k = l+1 ... r-1  k+=2
        tmp = func(s, l, k - 1, dp);
        a = tmp[0];
        b = tmp[1];
        tmp = func(s, k + 1, r, dp);
        c = tmp[0];
        d = tmp[1];
        if (s[k] == '&')
        {
          f += a * c + a * d + b * c;
          t += b * d;
        }
        else if (s[k] == '|')
        {
          f += a * c;
          t += a * d + b * c + b * d;
        }
        else
        {
          f += a * c + b * d;
          t += a * d + b * c;
        }
      }
    }
    vector<int> ft = {f, t};
    dp[l][r] = ft;
    return ft;
  }
};
