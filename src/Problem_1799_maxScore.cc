#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int bitCount(int x)
  {
    x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x & 0x0f0f0f0f) + ((x >> 4) & 0x0f0f0f0f);
    x = (x & 0x00ff00ff) + ((x >> 8) & 0x00ff00ff);
    x = (x & 0x0000ffff) + ((x >> 16) & 0x0000ffff);
    return x;
  }
  int maxScore(vector<int> &nums)
  {
    int m = nums.size();
    int all = 1 << m;
    vector<int> dp(all, 0);
    vector<vector<int>> gcds(m, vector<int>(m, 0));
    for (int i = 0; i < m; ++i)
    {
      for (int j = i + 1; j < m; ++j)
      {
        // 缓存nums[i]和nums[j]的gcd
        gcds[i][j] = gcd(nums[i], nums[j]);
      }
    }
    // 二进制枚举
    for (int s = 1; s < all; ++s)
    {
      // s的第i位为1表示原数组中第i个数未删除
      int t = bitCount(s);
      if (t & 1)
      {
        // 奇数个不能两两得分，直接忽略
        continue;
      }
      // 枚举最后选的两个数
      for (int i = 0; i < m; ++i)
      {
        if ((s >> i) & 1)
        {
          // nums[i]未删除
          for (int j = i + 1; j < m; ++j)
          {
            if ((s >> j) & 1)
            {
              // nums[j]未删除
              // 有t个数未删除，t为偶数，那么总共需要操作 t / 2次才能删除所有数
              // s ^ (1 << i) ^ (1 << j)表示从状态s中删除nums[i]和nums[j]
              dp[s] = max(dp[s], dp[s ^ (1 << i) ^ (1 << j)] + t / 2 * gcds[i][j]);
            }
          }
        }
      }
    }
    return dp[all - 1];
  }

  int gcd(int a, int b) { return b != 0 ? gcd(b, a % b) : a; }
};

void testMaxScore()
{
  Solution s;
  vector<int> n1 = {1, 2};
  vector<int> n2 = {3, 4, 6, 8};
  vector<int> n3 = {1, 2, 3, 4, 5, 6};
  EXPECT_EQ_INT(1, s.maxScore(n1));
  EXPECT_EQ_INT(11, s.maxScore(n2));
  EXPECT_EQ_INT(14, s.maxScore(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxScore();
  return 0;
}
