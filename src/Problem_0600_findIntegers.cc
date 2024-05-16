#include <vector>

using namespace std;

class Solution
{
 public:
  int findIntegers1(int n)
  {
    vector<int> cnt(31);
    // cnt[i] 的含义为，一共有i位的数中，有几个不含连续1的非负数
    cnt[0] = 1;  // 空串
    cnt[1] = 2;  // 0 和 1 共2个
    for (int len = 2; len <= 30; len++)
    {
      cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    return f(cnt, n, 30);
  }

  // cnt[len] : 二进制如果有len位，所有二进制状态中不存在连续的1的状态有多少个，辅助数组
  // 从num二进制形式的高位开始，当前来到第i位，之前的位完全和num一样
  // 返回<=num且不存在连续的1的状态有多少个
  int f(vector<int>& cnt, int num, int i)
  {
    if (i == -1)
    {
      return 1;  // num自身合法
    }
    int ans = 0;
    if ((num & (1 << i)) != 0)
    {
      // 当前位可填 0 或 1

      // 当前位填0
      ans += cnt[i];
      if ((num & (1 << (i + 1))) != 0)
      {
        // 如果num二进制状态，前一位是1，当前位也是1
        // 如果前缀保持和num一样，后续一定不合法了
        // 所以提前返回
        return ans;
      }
    }
    // 之前的高位和num一样，且合法，继续去i-1位递归
    ans += f(cnt, num, i - 1);
    return ans;
  }

  // 只是把方法1从递归改成迭代而已
  // 完全是等义改写，没有新东西
  int findIntegers2(int n)
  {
    vector<int> cnt(31);
    cnt[0] = 1;
    cnt[1] = 2;
    for (int len = 2; len <= 30; len++)
    {
      cnt[len] = cnt[len - 1] + cnt[len - 2];
    }
    int ans = 0;
    for (int i = 30; i >= -1; i--)
    {
      if (i == -1)
      {
        ans++;
        break;
      }
      if ((n & (1 << i)) != 0)
      {
        ans += cnt[i];
        if ((n & (1 << (i + 1))) != 0)
        {
          break;
        }
      }
    }
    return ans;
  }
};
