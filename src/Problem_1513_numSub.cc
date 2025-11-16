#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/number-of-substrings-with-only-1s/solutions/3820453/mei-ju-zi-chuan-you-duan-dian-jian-ji-xi-f5ry/
class Solution
{
 public:
  int numSub(string s)
  {
    const int mod = 1e9 + 7;
    long long ans = 0;
    int last0 = -1;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
      if (s[i] == '0')
      {
        // 记录上个 0 的位置
        last0 = i;
      }
      else
      {
        // 右端点为 i 的全 1 子串个数
        ans += i - last0;
      }
    }
    return ans % mod;
  }
};
