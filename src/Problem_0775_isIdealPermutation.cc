#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 归纳证明
  bool isIdealPermutation1(vector<int> &nums)
  {
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
      if (std::abs(nums[i] - i) > 1)
      {
        return false;
      }
    }
    return true;
  }

  int merge(vector<int> &nums, int L, int M, int R)
  {
    int n = R - L + 1;
    vector<int> help(n);
    int index = n - 1;
    int p1 = M;
    int p2 = R;
    int ans = 0;
    while (p1 >= L && p2 > M)
    {
      ans += nums[p1] > nums[p2] ? p2 - M : 0;
      help[index--] = nums[p1] > nums[p2] ? nums[p1--] : nums[p2--];
    }
    while (p1 >= L)
    {
      help[index--] = nums[p1--];
    }
    while (p2 > M)
    {
      help[index--] = nums[p2--];
    }
    for (int i = 0; i < n; i++)
    {
      nums[i + L] = help[i];
    }
    return ans;
  }

  int process(vector<int> &nums, int L, int R)
  {
    if (L == R)
    {
      return 0;
    }
    int M = L + (R - L) / 2;
    return process(nums, L, M) + process(nums, M + 1, R) + merge(nums, L, M, R);
  }

  // 求逆序对
  // https://github.com/yinghaoyu/algorithms/blob/master/sort/ReversePair.cc
  bool isIdealPermutation2(vector<int> &nums)
  {
    int n = nums.size();
    int a = 0;
    // 局部倒置
    for (int i = 0; i < n - 1; i++)
    {
      if (nums[i] > nums[i + 1])
      {
        a++;
      }
    }
    // 全局倒置 等价于 逆序对
    int b = process(nums, 0, n - 1);
    return a == b;
  }
};

void testIsIdealPermutation()
{
  Solution s;
  vector<int> n1 = {1, 0, 2};
  vector<int> n2 = {1, 2, 0};
  vector<int> n3 = {1, 2, 3, 0, 4, 5};
  EXPECT_TRUE(s.isIdealPermutation1(n1));
  EXPECT_FALSE(s.isIdealPermutation1(n2));
  EXPECT_FALSE(s.isIdealPermutation1(n3));
  EXPECT_TRUE(s.isIdealPermutation2(n1));
  EXPECT_FALSE(s.isIdealPermutation2(n2));
  EXPECT_FALSE(s.isIdealPermutation2(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testIsIdealPermutation();
  return 0;
}
