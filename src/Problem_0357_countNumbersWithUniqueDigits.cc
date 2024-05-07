// @sa https://www.bilibili.com/video/BV1cC4y1Q7r3/
class Solution
{
 public:
  // 数位 dp
  // 观察法
  int countNumbersWithUniqueDigits(int n)
  {
    if (n == 0)
    {
      return 1;
    }
    int ans = 10;
    // 1 : 10
    // 2 : 9 * 9
    // 3 : 9 * 9 * 8
    // 4 : 9 * 9 * 8 * 7
    // ...都累加起来...
    for (int s = 9, i = 9, k = 2; k <= n; i--, k++)
    {
      s *= i;
      ans += s;
    }
    return ans;
  }
};
