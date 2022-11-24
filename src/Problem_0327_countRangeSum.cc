#include <vector>

#include "UnitTest.h"

using namespace std;

// https://github.com/yinghaoyu/algorithms/blob/master/sort/CountOfRangeSum.cc

class Solution
{
 public:
  int merge(vector<int> &nums, int L, int M, int R, int lower, int upper)
  {
    int ans = 0;
    int windowL = L;
    int windowR = L;
    for (int i = M + 1; i <= R; i++)
    {
      int max = nums[i] - lower;
      int min = nums[i] - upper;
      while (windowR <= M && nums[windowR] <= max)
      {
        windowR++;
      }
      while (windowL <= M && nums[windowL] < min)
      {
        windowL++;
      }
      ans += windowR - windowL;
    }
    int n = R - L + 1;
    int p1 = L;
    int p2 = M + 1;
    int i = 0;
    vector<int> help(n);
    while (p1 <= M && p2 <= R)
    {
      help[i++] = nums[p1] <= nums[p2] ? nums[p1++] : nums[p2++];
    }
    while (p1 <= M)
    {
      help[i++] = nums[p1++];
    }
    while (p2 <= R)
    {
      help[i++] = nums[p2++];
    }
    for (int i = 0; i < n; i++)
    {
      nums[i + L] = help[i];
    }
    return ans;
  }

  int process(vector<int> &nums, int L, int R, int lower, int upper)
  {
    if (L == R)
    {
      return nums[L] >= lower && nums[L] <= upper ? 1 : 0;
    }
    int M = L + (R - L) / 2;
    return process(nums, L, M, lower, upper) + process(nums, M + 1, R, lower, upper) + merge(nums, L, M, R, lower, upper);
  }

  int countRangeSum(vector<int> &nums, int lower, int upper)
  {
    int n = nums.size();
    if (n == 0)
    {
      return 0;
    }
    vector<int> sum(n);
    sum[0] = nums[0];
    for (int i = 1; i < n; i++)
    {
      sum[i] = sum[i - 1] + nums[i];
    }
    return process(sum, 0, sum.size() - 1, lower, upper);
  }
};

void testCountRangeSum()
{
  Solution s;
  vector<int> n1 = {-2, 5, -1};
  vector<int> n2 = {0};
  EXPECT_EQ_INT(3, s.countRangeSum(n1, -2, 2));
  EXPECT_EQ_INT(1, s.countRangeSum(n2, 0, 0));
  EXPECT_SUMMARY;
}

int main()
{
  testCountRangeSum();
  return 0;
}
