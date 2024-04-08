#include <algorithm>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 双指针
  int minOperations(vector<int>& nums)
  {
    int n = nums.size();
    unordered_set<int> cnt(nums.begin(), nums.end());
    vector<int> sortedUniqueNums(cnt.begin(), cnt.end());
    std::sort(sortedUniqueNums.begin(), sortedUniqueNums.end());
    int ans = n;
    int j = 0;
    int m = sortedUniqueNums.size();
    // 记数组 nums 的长度为 n。经过若干次操作后，若数组变为连续的，那么数组的长度不会改变，仍然为
    // n，且数组最大值与最小值之差为 n−1，所有元素均不相同。
    // 可以反向考虑，假设最后连续的数组的最小值为
    // left，则最大值 right=left+n−1。

    // 枚举区间 [i, j] 最小值sortedUniqueNums[i]，最大值sortedUniqueNums[j]
    // 如果该区间最大值 sortedUniqueNums[j] <= sortedUniqueNums[i] + n - 1 之间
    // 说明可以保留，因为前面用unordered_set过滤了，现在已经是唯一值
    for (int i = 0; i < m; i++)
    {
      int right = sortedUniqueNums[i] + n - 1;
      while (j < m && sortedUniqueNums[j] <= right)
      {
        // j - i + 1 为保留的数
        ans = std::min(ans, n - (j - i + 1));
        j++;
      }
    }
    return ans;
  }
};
