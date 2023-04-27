#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
   // https://leetcode.cn/problems/maximum-sum-of-two-non-overlapping-subarrays/solution/tu-jie-mei-you-si-lu-yi-zhang-tu-miao-do-3lli/
  int maxSumTwoNoOverlap(vector<int> &nums, int firstLen, int secondLen)
  {
    int ans = 0;
    int n = nums.size();
    vector<int> sum(n + 1);
    for (int i = 0; i < n; i++)
    {
      // 前缀和
      sum[i + 1] = sum[i] + nums[i];
    }
    auto fun = [&](int firstLen, int secondLen) {
      int maxSumA = 0;
      // 枚举 B
      // 有效区间 [0, i) 不包含 i
      for (int i = firstLen + secondLen; i <= n; i++)
      {
        // 这个区间内 A 的最大值
        maxSumA = std::max(maxSumA, sum[i - secondLen] - sum[i - secondLen - firstLen]);
        ans = std::max(ans, maxSumA + sum[i] - sum[i - secondLen]);
      }
    };
    // A B 交换顺序都尝试一下
    fun(firstLen, secondLen);
    fun(secondLen, firstLen);
    return ans;
  }
};

void testMaxSumTwoNoOverlap()
{
  Solution s;
  vector<int> n1 = {0, 6, 5, 2, 2, 5, 1, 9, 4};
  vector<int> n2 = {3, 8, 1, 3, 2, 1, 8, 9, 0};
  vector<int> n3 = {2, 1, 5, 6, 0, 9, 5, 0, 3, 8};
  EXPECT_EQ_INT(20, s.maxSumTwoNoOverlap(n1, 1, 2));
  EXPECT_EQ_INT(29, s.maxSumTwoNoOverlap(n2, 3, 2));
  EXPECT_EQ_INT(31, s.maxSumTwoNoOverlap(n3, 4, 3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxSumTwoNoOverlap();
  return 0;
}
