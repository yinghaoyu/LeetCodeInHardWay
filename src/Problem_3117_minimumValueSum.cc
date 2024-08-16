#include <unordered_map>
#include <vector>

using namespace std;

class Solution
{
 private:
  static constexpr int INF = (1 << 20) - 1;

  vector<unordered_map<int, int>> dp;

 public:
  int minimumValueSum(vector<int>& nums, vector<int>& andValues)
  {
    int n = nums.size();
    int m = andValues.size();
    dp.resize(m * n);
    int ans = f(0, 0, INF, nums, andValues);
    return ans < INF ? ans : -1;
  }

  // 记忆化搜索
  // i 数组 nums[i] 的当前位置
  // j 匹配 andValues[j] 的当前位置
  // 当前子数组的 & 值
  int f(int i, int j, int cur, vector<int>& nums, vector<int>& andValues)
  {
    int n = nums.size();
    int m = andValues.size();
    int key = i * m + j;  // 二维数组转一维数组
    if (i == n && j == m)
    {
      // 刚好匹配
      return 0;
    }
    if (i == n || j == m)
    {
      // 不合法
      return INF;
    }
    if (dp[key].count(cur))
    {
      return dp[key][cur];
    }
    // 根据 & 运算符的性质，只要一直 & 一定是不变或者变小
    cur &= nums[i];
    if ((cur & andValues[j]) < andValues[j])
    {
      // 不合法
      return INF;
    }
    // 尝试继续匹配当前 andValues[j]
    int ans = f(i + 1, j, cur, nums, andValues);
    if (cur == andValues[j])
    {
      // 符合要求时，可以匹配下一个 andValues[j]，注意这里要让 cur = INF
      ans = std::min(ans, f(i + 1, j + 1, INF, nums, andValues) + nums[i]);
    }
    dp[key][cur] = ans;
    return ans;
  }
};
