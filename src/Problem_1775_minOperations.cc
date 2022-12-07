#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int help(vector<int> &h1, vector<int> &h2, int diff)
  {
    // 增大h1，减少h2，使得diff减少到0
    // h[i]是可以获得的i的减少量的个数
    vector<int> h(7, 0);
    for (int i = 1; i < 7; ++i)
    {
      // 一定要保证h1是更小和数组数据
      // 假设h1是更大和的数组数据，再增大
      // 假设h2是更小和的数据数据，再减小，这会使得diff越来越大

      // h1[i]个i最多可以增大到6，增大量是6-i
      h[6 - i] += h1[i];
      // h2[i]个i最多可以减少到1，减少量是i-1
      h[i - 1] += h2[i];
    }
    int res = 0;
    // 贪心 从5到1 遍历改变量i,改变量大那么改变的数字就少
    for (int i = 5; i && diff > 0; --i)
    {
      // 看使得diff减少到0需要多少个i，如果不够，h[i]个i全部用上
      int t = std::min((diff + i - 1) / i, h[i]);
      // 一次改变t个数
      res += t;
      // diff的减少量：减少了t个i
      diff -= t * i;
    }
    return res;
  }

  int minOperations(vector<int> &nums1, vector<int> &nums2)
  {
    int n = nums1.size(), m = nums2.size();
    if (6 * n < m || 6 * m < n)
    {
      // num1所有元素取最大值6的和，都不能达到num2数组所有元素取最小值1的和
      return -1;
    }
    vector<int> cnt1(7, 0), cnt2(7, 0);
    int diff = 0;
    for (auto &i : nums1)
    {
      // 统计1...6出现的频率
      ++cnt1[i];
      diff += i;
    }
    for (auto &i : nums2)
    {
      ++cnt2[i];
      diff -= i;
    }
    if (diff > 0)
    {
      // sum(num1) > sum(num2)
      return help(cnt2, cnt1, diff);
    }
    else if (diff < 0)
    {
      // sum(num1) < sum(num2)
      // 注意这里的cnt1和cnt2的顺序不能换
      return help(cnt1, cnt2, -diff);
    }
    else
    {
      // sum(num1) == sum(num2)
      return 0;
    }
  }
};

void testMinOperations()
{
  Solution s;
  vector<int> n1 = {1, 2, 3, 4, 5, 6};
  vector<int> n2 = {1, 1, 2, 2, 2, 2};
  EXPECT_EQ_INT(3, s.minOperations(n1, n2));
  vector<int> n3 = {1, 1, 1, 1, 1, 1};
  vector<int> n4 = {6};
  EXPECT_EQ_INT(-1, s.minOperations(n3, n4));
  vector<int> n5 = {6, 6};
  vector<int> n6 = {1};
  EXPECT_EQ_INT(3, s.minOperations(n5, n6));
  EXPECT_SUMMARY;
}

int main()
{
  testMinOperations();
  return 0;
}
