#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  long long process(vector<int> &nums, int index, vector<int> seq)
  {
    if (index == nums.size())
    {
      std::sort(seq.begin(), seq.end());
      return seq.size() > 0 ? *seq.rbegin() - *seq.begin() : 0;
    }
    seq.push_back(nums[index]);
    long long p1 = process(nums, index + 1, seq);
    seq.pop_back();
    long long p2 = process(nums, index + 1, seq);
    return (p1 + p2) % ((long long) 1e9 + 7);
  }

  // 暴力尝试
  int sumSubseqWidths1(vector<int> &nums)
  {
    vector<int> seq;
    return process(nums, 0, seq);
  }

  // 每个在 i 位置的数都可能在子集中是最大值或者最小值
  // 而作为最大值时对最终结果的贡献是正的，做最小值的时候对结果的贡献是负的（因为做最大值是它减去其他值，做最小值是其他值减去它，该元素的符号一正一负）
  // 所以作为最大值的次数减去最小值的次事就是这个值对最终结果的贡献次数，乘上这个值本身就是它的贡献总数值
  int sumSubseqWidths2(vector<int> &nums)
  {
    long long ans = 0;
    long long mod = 1e9 + 7;
    int n = nums.size();
    vector<long long> pow(n);
    pow[0] = 1L;
    for (int i = 1; i < n; i++)
    {
      // 预处理，计算2 ^ i
      pow[i] = (pow[i - 1] << 1) % mod;
    }

    sort(nums.begin(), nums.end());
    // 1 2 3 4 5 6 7
    //       ↑
    //       i
    // 对于nums[i]，
    // 前面有 i 个数都比 nums[i]小，以 nums[i] 作为最大值的子序列有 2 ^ i 个
    // 后面有 n - i - 1 个数比 nums[i] 大，以 nums[i] 作为最小值的子序列有 2 ^ (n - i - 1) 个
    for (int i = 0; i < n; i++)
    {
      ans = (ans + (pow[i] - pow[n - i - 1]) * nums[i]) % mod;
    }
    return ans;
  }
};

void testSumSubseqWidths()
{
  Solution s;
  vector<int> n1 = {2, 1, 3};
  vector<int> n2 = {2};
  vector<int> n3 = {5,  69, 89, 92, 31, 16,  25, 45, 63, 40, 16, 56, 24, 40, 75, 82, 40, 12, 50, 62, 92, 44, 67, 38, 92,
                    22, 91, 24, 26, 21, 100, 42, 23, 56, 64, 43, 95, 76, 84, 79, 89, 4,  16, 94, 16, 77, 92, 9,  30, 13};
  EXPECT_EQ_INT(6, s.sumSubseqWidths1(n1));
  EXPECT_EQ_INT(0, s.sumSubseqWidths1(n2));
  EXPECT_EQ_INT(6, s.sumSubseqWidths2(n1));
  EXPECT_EQ_INT(0, s.sumSubseqWidths2(n2));
  EXPECT_EQ_INT(857876214, s.sumSubseqWidths2(n3));
  EXPECT_SUMMARY;
}

int main()
{
  testSumSubseqWidths();
  return 0;
}
