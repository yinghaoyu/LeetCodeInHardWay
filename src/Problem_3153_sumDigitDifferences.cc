#include <vector>

using namespace std;

class Solution
{
 public:
  long long sumDigitDifferences(vector<int>& nums)
  {
    long long ans = 0;
    int n = nums.size();
    while (nums[0] > 0)
    {
      vector<int> cnt(10);
      for (int i = 0; i < n; i++)
      {
        // 统计出现次数
        cnt[nums[i] % 10]++;
        nums[i] /= 10;
      }
      for (int i = 0; i < 10; i++)
      {
        // 根据排列组合，自己出现了cnt[i]次，其他数就出现了n - cnt[i]次
        ans += (long long) (n - cnt[i]) * cnt[i];
      }
    }
    // 这个次数，会在计算其他数字时也被计算一次，所以最后结果要除以 2
    return ans / 2;
  }
};
