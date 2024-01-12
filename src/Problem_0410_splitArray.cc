#include <cstdint>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 经典二分法
  // 时间复杂度O(n * log(sum))，额外空间复杂度O(1)
  int splitArray(vector<int>& nums, int k)
  {
    long sum = 0;
    for (int num : nums)
    {
      sum += num;
    }
    long ans = 0;
    // 当子数组个自和最大值m变大时，被分割的parts要么不变，要么变小，符合单调性
    //[0, sum] 二分
    for (long l = 0, r = sum, m, need; l <= r;)
    {
      // 中点m
      m = (r - l) / 2 + l;
      // 必须让数组每一部分的累加和 <= m，请问划分成几个部分才够!
      need = f(nums, m);
      if (need <= k)
      {
        // 达标
        ans = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return ans;
  }

  // 必须让数组arr每一部分的累加和 <= limit，请问划分成几个部分才够!
  // 返回需要的部分数量
  int f(vector<int>& arr, long limit)
  {
    int parts = 1;
    int sum = 0;
    for (int num : arr)
    {
      if (num > limit)
      {
        // 不存在这个方法
        return INT32_MAX;
      }
      if (sum + num > limit)
      {
        parts++;
        sum = num;
      }
      else
      {
        sum += num;
      }
    }
    return parts;
  }
};

void test()
{
  Solution s;
  vector<int> n1 = {7, 2, 5, 10, 8};
  vector<int> n2 = {1, 2, 3, 4, 5};
  EXPECT_EQ_INT(18, s.splitArray(n1, 2));
  EXPECT_EQ_INT(9, s.splitArray(n2, 2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
