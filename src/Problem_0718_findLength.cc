#include <vector>

using namespace std;

class Solution
{
 public:
  int findLength1(vector<int>& nums1, vector<int>& nums2)
  {
    int n = nums1.size();
    int m = nums2.size();
    // dp[i][j] 表示 nums1[i...] 和 nums2[j...] 的最长公共前缀
    vector<vector<int>> dp(n + 1, vector<int>(n + 1));
    int ans = 0;
    for (int i = n - 1; i >= 0; i--)
    {
      for (int j = m - 1; j >= 0; j--)
      {
        dp[i][j] = nums1[i] == nums2[j] ? dp[i + 1][j + 1] + 1 : 0;
        ans = std::max(ans, dp[i][j]);
      }
    }
    return ans;
  }

  // 获取这个区间内最长的重复子数组是多长
  int maxLength(vector<int>& arr1, vector<int>& arr2, int A, int B, int len)
  {
    int ans = 0;
    int k = 0;
    for (int i = 0; i < len; i++)
    {
      if (arr1[A + i] == arr2[B + i])
      {
        k++;
      }
      else
      {
        // 注意这里是清0，而不是 break
        k = 0;
      }
      ans = std::max(ans, k);
    }
    return ans;
  }

  int findLength2(vector<int>& nums1, vector<int>& nums2)
  {
    int n = nums1.size();
    int m = nums2.size();
    int ans = 0;
    // nums1 数组左移 i 个元素与数组 nums2 对齐
    for (int i = 0; i < n; i++)
    {
      int len = std::min(m, n - i);
      int maxLen = maxLength(nums1, nums2, i, 0, len);
      ans = std::max(ans, maxLen);
    }
    // nums2 数组左移 i 个元素与数组 nums1 对齐
    for (int i = 0; i < n; i++)
    {
      int len = std::min(n, m - i);
      int maxLen = maxLength(nums1, nums2, 0, i, len);
      ans = std::max(ans, maxLen);
    }
    return ans;
  }

  // TODO: 二分查找 + hash
};
