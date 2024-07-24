#include <algorithm>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 private:
  static constexpr int mod = 1e9 + 7;
  static constexpr int inf = 0x3f3f3f3f;

 public:
  int sumOfPowers(vector<int>& nums, int k)
  {
    int n = nums.size();
    int ans = 0;

    // d[i][p][v] 表示以 i 为结尾时，有多少个长度为 p 且能量为 v 的子序列
    vector<vector<unordered_map<int, int>>> dp(n, vector<unordered_map<int, int>>(k + 1));
    std::sort(nums.begin(), nums.end());
    // 插入第 i 个元素
    for (int i = 0; i < n; i++)
    {
      // 长度为 1 默认不存在，序列至少有 2 个元素才有能量
      dp[i][1][inf] = 1;
      // 枚举第i个元素插入d的位置，插入在 j 后
      for (int j = 0; j < i; j++)
      {
        // 因为排序后序列有序，插入第 i 个元素，需要重新计算新序列的能量
        int diff = std::abs(nums[i] - nums[j]);
        // 枚举必须以 j 元素结尾，序列的长度
        for (int p = 2; p <= k; p++)
        {
          for (auto& [v, cnt] : dp[j][p - 1])
          {
            // 计算新序列的能量值
            dp[i][p][std::min(diff, v)] = (dp[i][p][std::min(diff, v)] + cnt) % mod;
          }
        }
      }

      // 统计能量值总和
      for (auto& [v, cnt] : dp[i][k])
      {
        ans = (ans + 1ll * v * cnt % mod) % mod;
      }
    }
    return ans;
  }
};
