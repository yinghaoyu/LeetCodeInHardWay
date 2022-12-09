#include <math.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int binarySearch(int n, int t)
  {
    int l = 0;
    int r = n;
    int index = -1;
    while (l <= r)
    {
      int m = l + (r - l) / 2;
      if (pow(3, m) <= t)
      {
        index = m;
        l = m + 1;
      }
      else
      {
        r = m - 1;
      }
    }
    return index;
  }

  // 暴力解
  bool checkPowersOfThree1(int n)
  {
    int pre = n;
    while (n != 0 && pre != -1)
    {
      // 找到第一个满足 3 ^ cur <= n
      int cur = binarySearch(pre, n);
      if (cur == pre)
      {
        // distinct power
        break;
      }
      // 根据单调性，这个时候必定要减去
      n -= pow(3, cur);
      pre = cur;
    }
    return n == 0;
  }

  bool checkPowersOfThree2(int n) { return dfs(1, n); }

  // 递归
  bool dfs(int cur, int n)
  {
    if (n == 0)
    {
      // base case
      return true;
    }
    if (n < 0 || cur > n)
    {
      // n越界，或者cur越界
      return false;
    }
    bool p1 = dfs(cur * 3, n);        // 不减
    bool p2 = dfs(cur * 3, n - cur);  // 减
    return p1 | p2;
  }

  bool checkPowersOfThree3(int n)
  {
    // 将n转换为3进制，如果每一位均不为2，则答案为true
    // 例如 12 = 110 满足要求
    //      21 = 210 不满足要求
    while (n)
    {
      if (n % 3 == 2)
      {
        return false;
      }
      n /= 3;
    }
    return true;
  }
};

void testCheckPowersOfThree()
{
  Solution s;
  EXPECT_TRUE(s.checkPowersOfThree1(12));
  EXPECT_TRUE(s.checkPowersOfThree1(91));
  EXPECT_TRUE(s.checkPowersOfThree1(85));
  EXPECT_FALSE(s.checkPowersOfThree1(21));
  EXPECT_TRUE(s.checkPowersOfThree2(12));
  EXPECT_TRUE(s.checkPowersOfThree2(91));
  EXPECT_TRUE(s.checkPowersOfThree2(85));
  EXPECT_FALSE(s.checkPowersOfThree2(21));
  EXPECT_TRUE(s.checkPowersOfThree3(12));
  EXPECT_TRUE(s.checkPowersOfThree3(91));
  EXPECT_TRUE(s.checkPowersOfThree3(85));
  EXPECT_FALSE(s.checkPowersOfThree3(21));
  EXPECT_SUMMARY;
}

int main()
{
  testCheckPowersOfThree();
  return 0;
}
