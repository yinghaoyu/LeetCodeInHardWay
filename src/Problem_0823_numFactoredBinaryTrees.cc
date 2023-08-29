#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution
{
 public:
  int numFactoredBinaryTrees(vector<int> &arr)
  {
    // 排序，方便找到符合子节点的区间
    std::sort(arr.begin(), arr.end());
    int n = arr.size();
    // dp[i] 表示以 arr[i] 为根节点符合条件的树的数量
    vector<long long> dp(n);
    const int mod = 1e9 + 7;
    long long ans = 0;
    for (int i = 0; i < n; i++)
    {
      // 没有子节点，自己单独可以成树
      dp[i] = 1;
      for (int left = 0, right = i - 1; left <= right; left++)
      {
        while (left <= right && (long long) arr[left] * arr[right] > arr[i])
        {
          // 缩小窗口
          right--;
        }
        if (left <= right && (long long) arr[left] * arr[right] == arr[i])
        {
          if (left != right)
          {
            // 因为 arr 的值是唯一的，索引不同值也不同
            // 不同的值左右节点可以互换
            dp[i] = (dp[i] + dp[left] * dp[right] * 2) % mod;
          }
          else
          {
            dp[i] = (dp[i] + dp[left] * dp[right]) % mod;
          }
        }
      }
      ans = (ans + dp[i]) % mod;
    }
    return ans;
  }
};
