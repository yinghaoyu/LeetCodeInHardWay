#include <string>
#include <vector>

using namespace std;

// 康拓展开
// @sa https://zhuanlan.zhihu.com/p/369098927

// TODO: figure it out.
class Solution
{
 public:
  string getPermutation(int n, int k)
  {
    // 求 1 ... n 的阶乘
    vector<int> factorial(n);
    factorial[0] = 1;
    for (int i = 1; i < n; i++)
    {
      factorial[i] = factorial[i - 1] * i;
    }

    --k;
    string ans;
    vector<int> valid(n + 1, 1);
    for (int i = 1; i <= n; ++i)
    {
      int order = k / factorial[n - i] + 1;
      for (int j = 1; j <= n; ++j)
      {
        order -= valid[j];
        if (!order)
        {
          ans += (j + '0');
          valid[j] = 0;
          break;
        }
      }
      k %= factorial[n - i];
    }
    return ans;
  }
};
