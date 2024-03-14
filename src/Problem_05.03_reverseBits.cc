#include <vector>

using namespace std;

class Solution
{
 public:
  // 动态规划
  int reverseBits(int num)
  {
    // dp[i][0]记录不插入1时, 以i为连续1尾部的长度
    // dp[i][0]记录最新遇到的0二进制位插入1时,以i为连续1尾部的长度
    vector<vector<int>> dp(32, vector<int>(2));
    dp[0][0] = num & 1;
    dp[0][1] = 1;
    int ans = 0;
    for (int i = 1; i < 32; i++)
    {
      if ((num >> i) & 1)
      {
        // 遇到 1

        // 不翻转，长度显然增加 1
        dp[i][0] = dp[i - 1][0] + 1;
        // 翻转，在前面0...i-1位
        dp[i][1] = dp[i - 1][1] + 1;
      }
      else
      {
        // 遇到 0

        // 不翻转，连续1子串到此戛然而止
        dp[i][0] = 0;
        // 翻转，只能在 i 位翻转，前面必须全是 1
        dp[i][1] = dp[i - 1][0] + 1;
      }
      // 因为允许翻转一次的字串长度必然 >= 不允许翻转的全1子串长度，
      // 因此我们只需遍历dp[i][1]中的最大值即可。
      ans = std::max(ans, dp[i][1]);
    }
    return ans;
  }
};
