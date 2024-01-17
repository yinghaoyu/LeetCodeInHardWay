#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 经典二分法
  // 时间复杂度O(N*log(sum))，额外空间复杂度O(1)
  long long maxRunTime1(int n, vector<int>& batteries)
  {
    long sum = 0;
    for (int x : batteries)
    {
      sum += x;
    }
    long ans = 0;
    // 运行 m 分钟时间越长，同时运行的电脑数量 num 越小，符合单调性
    // [0, sum]不停二分
    for (long l = 0, r = sum, m; l <= r;)
    {
      // 让num台电脑同时运行m分钟，能不能做到
      m = l + (r - l) / 2;
      if (f(batteries, n, m))
      {
        ans = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return ans;
  }

  // 让num台电脑共同运行time分钟，能不能做到
  bool f(vector<int>& arr, int num, long time)
  {
    // 碎片电量总和
    long sum = 0;
    for (int x : arr)
    {
      if (x > time)
      {
        // 电池在使用的过程中，是独占的
        num--;
      }
      else
      {
        // x <= time，是碎片电池
        sum += x;
      }
    }
    if (sum >= (long) num * time)
    {
      // 碎片电量 >= 台数 * 要求
      return true;
    }
    return false;
  }

  // 二分 + 贪心
  // 时间复杂度O(N * logMax)，额外空间复杂度O(1)
  long long maxRunTime2(int n, vector<int>& batteries)
  {
    int max = 0;
    long sum = 0;
    for (int x : batteries)
    {
      max = std::max(max, x);
      sum += x;
    }
    // 相对方法一，就是增加了这里的逻辑
    if (sum > (long) max * n)
    {
      // 所有电池的最大电量是max
      // 如果此时sum > (long) max * n，
      // 说明 : 最终的供电时间一定在 >= max，而如果最终的供电时间 >= max
      // 说明 : 对于最终的答案X来说，所有电池都是课上讲的"碎片拼接"的概念
      // 那么寻找 ? * n <= sum 的情况中，尽量大的 ? 即可
      // 即sum / num
      return sum / n;
    }
    // 最终的供电时间一定在 < max范围上
    // [0, sum]二分范围，可能定的比较粗，虽然不影响，但毕竟是有点慢
    // [0, max]二分范围！更精细的范围，二分次数会变少
    int ans = 0;
    for (int l = 0, r = max, m; l <= r;)
    {
      m = l + (r - l) / 2;
      if (f(batteries, n, m))
      {
        ans = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return ans;
  }
};

void test()
{
  Solution s;
  vector<int> b1 = {3, 3, 3};
  vector<int> b2 = {1, 1, 1, 1};
  EXPECT_EQ_INT(4, s.maxRunTime1(2, b1));
  EXPECT_EQ_INT(2, s.maxRunTime1(2, b2));
  EXPECT_EQ_INT(4, s.maxRunTime2(2, b1));
  EXPECT_EQ_INT(2, s.maxRunTime2(2, b2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
