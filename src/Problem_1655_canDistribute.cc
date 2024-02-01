#include <algorithm>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 private:
  // 当前来到的数字，编号index，个数cnt[index]
  // status : 订单状态，1还需要去满足，0已经满足过了
  bool f(vector<int>& cnt, vector<int>& sum, int status, int index, vector<vector<int>>& dp)
  {
    if (status == 0)
    {
      return true;
    }
    // status != 0
    if (index == cnt.size())
    {
      return false;
    }
    if (dp[status][index] != 0)
    {
      return dp[status][index] == 1;
    }
    bool ans = false;
    int k = cnt[index];
    // 这是整个实现最核心的枚举
    // j枚举了status的所有子集状态
    // 建议记住
    for (int j = status; j > 0; j = (j - 1) & status)
    {
      if (sum[j] <= k && f(cnt, sum, status ^ j, index + 1, dp))
      {
        ans = true;
        break;
      }
    }
    if (!ans)
    {
      ans = f(cnt, sum, status, index + 1, dp);
    }
    dp[status][index] = ans ? 1 : -1;
    return ans;
  }

 public:
  bool canDistribute(vector<int>& nums, vector<int>& quantity)
  {
    std::sort(nums.begin(), nums.end());
    int n = 1;
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i - 1] != nums[i])
      {
        n++;
      }
    }
    // 总共有 n 个不同的数，第 i 个数有 cnt[i] 个
    vector<int> cnt(n);
    int c = 1;
    for (int i = 1, j = 0; i < nums.size(); i++)
    {
      if (nums[i - 1] != nums[i])
      {
        cnt[j++] = c;
        c = 1;
      }
      else
      {
        c++;
      }
    }
    cnt[n - 1] = c;
    int m = quantity.size();
    vector<int> sum(1 << m);
    // 下面这个枚举是生成quantity中的每个子集，所需要数字的个数
    for (int i = 0, v, h; i < quantity.size(); i++)
    {
      v = quantity[i];
      h = 1 << i;
      for (int j = 0; j < h; j++)
      {
        sum[h | j] = sum[j] + v;
      }
    }
    vector<vector<int>> dp(1 << m, vector<int>(n));
    return f(cnt, sum, (1 << m) - 1, 0, dp);
  }
};
