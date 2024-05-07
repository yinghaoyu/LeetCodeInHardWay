#include <string>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 数位dp
// @sa https://www.bilibili.com/video/BV1cC4y1Q7r3/
class Solution
{
 public:
  // 尝试
  int atMostNGivenDigitSet1(vector<string>& digits, int n)
  {
    int tmp = n / 10;
    int len = 1;
    int offset = 1;
    while (tmp > 0)
    {
      tmp /= 10;
      len++;
      offset *= 10;
    }
    return f1(digits, n, offset, len, 0, 0);
  }

  // offset是辅助变量，完全由len决定，只是为了方便提取num中某一位数字，不是关键变量
  // 还剩下len位没有决定
  // 如果之前的位已经确定比num小，那么free == 1，表示接下的数字可以自由选择
  // 如果之前的位和num一样，那么free == 0，表示接下的数字不能大于num当前位的数字
  // 如果之前的位没有使用过数字，fix == 0
  // 如果之前的位已经使用过数字，fix == 1
  // 返回最终<=num的可能性有多少种
  int f1(vector<string>& digits, int n, int offset, int len, int free, int fix)
  {
    if (len == 0)
    {
      return fix == 1 ? 1 : 0;
    }
    int ans = 0;
    // n在当前位的数字
    int cur = (n / offset) % 10;
    if (fix == 0)
    {
      // 之前从来没有选择过数字
      // 当前依然可以不要任何数字，累加后续的可能性
      ans += f1(digits, n, offset / 10, len - 1, 1, 0);
    }
    if (free == 0)
    {
      // 不能自由选择的情况
      for (string& str : digits)
      {
        int i = stoi(str);
        if (i < cur)
        {
          ans += f1(digits, n, offset / 10, len - 1, 1, 1);
        }
        else if (i == cur)
        {
          ans += f1(digits, n, offset / 10, len - 1, 0, 1);
        }
        else
        {
          // i > cur
          break;
        }
      }
    }
    else
    {
      // 可以自由选择的情况
      ans += digits.size() * f1(digits, n, offset / 10, len - 1, 1, 1);
    }
    return ans;
  }

  // 优化版，把前面 i < cur 的情况打表
  int atMostNGivenDigitSet2(vector<string>& digits, int n)
  {
    int len = 1;
    int offset = 1;
    int tmp = n / 10;
    while (tmp > 0)
    {
      tmp /= 10;
      len++;
      offset *= 10;
    }
    // cnt[i] : 已知前缀比num小，剩下i位没有确定，请问前缀确定的情况下，一共有多少种数字排列
    // cnt[0] = 1，表示后续已经没有了，前缀的状况都已确定，那么就是1种
    // cnt[1] = m
    // cnt[2] = m * m
    // cnt[3] = m * m * m
    // ...
    vector<int> cnt(len);
    cnt[0] = 1;
    int ans = 0;
    int m = digits.size();
    for (int i = m, k = 1; k < len; k++, i *= m)
    {
      cnt[k] = i;
      ans += i;
    }
    return ans + f2(digits, cnt, n, offset, len);
  }

  // offset是辅助变量，由len确定，方便提取num中某一位数字
  // 还剩下len位没有决定，之前的位和num一样
  // 返回最终<=num的可能性有多少种
  int f2(vector<string>& digits, vector<int>& cnt, int num, int offset, int len)
  {
    if (len == 0)
    {
      // num自己
      return 1;
    }
    // cur是num当前位的数字
    int cur = (num / offset) % 10;
    int ans = 0;
    for (string& str : digits)
    {
      int i = stoi(str);
      if (i < cur)
      {
        ans += cnt[len - 1];
      }
      else if (i == cur)
      {
        ans += f2(digits, cnt, num, offset / 10, len - 1);
      }
      else
      {
        break;
      }
    }
    return ans;
  }
};

void testAtMostNGivenDigitSet()
{
  Solution s;
  vector<string> digits1 = {"1", "3", "5", "7"};
  vector<string> digits2 = {"1", "4", "9"};
  vector<string> digits3 = {"7"};

  EXPECT_EQ_INT(20, s.atMostNGivenDigitSet2(digits1, 100));
  EXPECT_EQ_INT(29523, s.atMostNGivenDigitSet2(digits2, 1000000000));
  EXPECT_EQ_INT(1, s.atMostNGivenDigitSet2(digits3, 8));

  EXPECT_SUMMARY;
}

int main()
{
  testAtMostNGivenDigitSet();
  return 0;
}
