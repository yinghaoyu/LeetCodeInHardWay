#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 找到左边第一个<=的位置
  vector<int> nearLessEqualLeft(vector<int> &arr)
  {
    int n = arr.size();
    vector<int> left(n);
    vector<int> stack;
    for (int i = n - 1; i >= 0; i--)
    {
      // 单调递增栈，不包括等于
      while (!stack.empty() && arr[stack.back()] >= arr[i])
      {
        int cur = stack.back();
        stack.pop_back();
        left[cur] = i;
      }
      stack.push_back(i);
    }
    while (!stack.empty())
    {
      int cur = stack.back();
      stack.pop_back();
      left[cur] = -1;
    }
    return left;
  }

  // 找到右边第一个<的位置
  vector<int> nearLessRight(vector<int> &arr)
  {
    int n = arr.size();
    vector<int> right(n);
    vector<int> stack;
    for (int i = 0; i < n; i++)
    {
      // 单调递增栈，等于包含在内
      while (!stack.empty() && arr[stack.back()] > arr[i])
      {
        int cur = stack.back();
        stack.pop_back();
        right[cur] = i;
      }
      stack.push_back(i);
    }
    while (!stack.empty())
    {
      int cur = stack.back();
      stack.pop_back();
      right[cur] = n;
    }
    return right;
  }

  // 当 arr 存在重复元素，且该元素作为子数组最小值时，最远左右端点的边界越过重复元素时，导致重复统计子数组
  // x x x x a x x x a x x x
  //     ↑   ↑           ↑
  //     L   L'          R
  // 如果不区分两个相等的元素 a，那么会重复计算子数组[L, R]
  // 将 最远左右边界 的一端，从严格 < 调整为 <=，从而实现半开半闭的效果
  // 这样,
  // 对于第一个 a，计算的子数组为[L, R]
  // 对于第二个 a，计算的子数组为[L', R]
  int sumSubarrayMins(vector<int> &arr)
  {
    int n = arr.size();
    long ans = 0;
    vector<int> left = nearLessEqualLeft(arr);
    vector<int> right = nearLessRight(arr);
    for (int i = 0; i < n; i++)
    {
      long start = i - left[i];
      long end = right[i] - i;
      ans += start * end * arr[i];
      ans %= 1000000007;
    }
    return ans;
  }
};

void testSumSubarrayMins()
{
  Solution s;
  vector<int> n1 = {3, 1, 2, 4};
  vector<int> n2 = {11, 81, 94, 43, 3};
  EXPECT_EQ_INT(17, s.sumSubarrayMins(n1));
  EXPECT_EQ_INT(444, s.sumSubarrayMins(n2));
  EXPECT_SUMMARY;
}

int main()
{
  testSumSubarrayMins();
  return 0;
}
