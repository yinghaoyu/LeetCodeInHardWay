#include <iostream>
#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int process(string &sn, int index, int mask, int same, vector<vector<int>> &dp)
  {
    if (index == sn.length())
    {
      return 1;
    }
    if (!same && dp[index][mask] >= 0)
    {
      // 注意！！！
      // 假设当前需要填入第 index 位，且前面填入的数字与 n 对应位置的数字不相同
      // 那么需要求得的不重复数字的正整数个数只与 mask 相关，这时才可以记忆化
      return dp[index][mask];
    }
    int ans = 0;
    // 如果前缀的数字与sn严格相同，那么下一个数只能填 <= s[index]的，否则可以填[0,9]
    // 比如 sn = "321"，这时前面填了3，对于 3?? ，第一个问号只能填 <=2的，以保证最后所得的数 <= sn
    int t = same ? (sn[index] - '0') : 9;
    for (int i = 0; i <= t; i++)
    {
      if (mask & (1 << i))
      {
        // 有重复数字
        continue;
      }
      // 如果前缀为0，且当前填入的数字也是0，那么nmask = 0
      // 如果前缀非0，那么nmask = (mask | ( 1 << i ))
      int nmask = (mask == 0 && i == 0) ? mask : (mask | (1 << i));
      // 当same && i == t时，说明前面填的数与sn一致
      ans += process(sn, index + 1, nmask, same && i == t, dp);
    }
    if (!same)
    {
      dp[index][mask] = ans;
    }
    return ans;
  }

  int numDupDigitsAtMostN(int n)
  {
    string sn = std::to_string(n);
    int M = sn.size();
    vector<vector<int>> dp(M, vector<int>(1 << 10, -1));
    // [0, n]有 n+1 个数，减去 所有数字都不相同的数 的个数
    return n + 1 - process(sn, 0, 0, true, dp);
  }
};

void testNumDupDigitsAtMostN()
{
  Solution s;
  EXPECT_EQ_INT(1, s.numDupDigitsAtMostN(20));
  EXPECT_EQ_INT(10, s.numDupDigitsAtMostN(100));
  EXPECT_EQ_INT(262, s.numDupDigitsAtMostN(1000));
  EXPECT_SUMMARY;
}

int main()
{
  testNumDupDigitsAtMostN();
  return 0;
}
