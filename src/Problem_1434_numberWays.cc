#include <vector>

using namespace std;

class Solution
{
 private:
  static const int MOD = 1e9 + 7;

  // m : 帽子颜色的最大值, 1 ~ m
  // n : 人的数量，0 ~ n-1
  // i : 来到了什么颜色的帽子
  // s : n个人，谁没满足状态就是0，谁满足了状态就是1
  // dp : 记忆化搜索的表
  // 返回 : 有多少种方法
  int f1(vector<int>& arr, int m, int n, int i, int s, vector<vector<int>>& dp)
  {
    if (s == (1 << n) - 1)
    {
      // 所有人都满足了
      return 1;
    }
    // 还有人没满足
    if (i == m + 1)
    {
      // 所有帽子都用完了
      return 0;
    }
    if (dp[i][s] != -1)
    {
      return dp[i][s];
    }
    // 可能性1 : i颜色的帽子，不分配给任何人
    int ans = f1(arr, m, n, i + 1, s, dp);
    // 可能性2 : i颜色的帽子，分配给可能的每一个人
    int cur = arr[i];
    // 用for循环从0 ~ n-1枚举每个人
    for (int p = 0; p < n; p++)
    {
      // 分配给没满足，且这顶帽子可以使他满足的人
      if ((cur & (1 << p)) != 0 && (s & (1 << p)) == 0)
      {
        ans = (ans + f1(arr, m, n, i + 1, s | (1 << p), dp)) % MOD;
      }
    }
    dp[i][s] = ans;
    return ans;
  }

  int f2(vector<int>& arr, int m, int n, int i, int s, vector<vector<int>>& dp)
  {
    if (s == (1 << n) - 1)
    {
      return 1;
    }
    if (i == m + 1)
    {
      return 0;
    }
    if (dp[i][s] != -1)
    {
      return dp[i][s];
    }
    int ans = f2(arr, m, n, i + 1, s, dp);
    int cur = arr[i];
    // 不用for循环枚举
    // 从当前帽子中依次提取能满足的人
    // 提取出二进制状态中最右侧的1，讲解030-异或运算，题目5，Brian Kernighan算法
    // cur :
    // 0 0 0 1 1 0 1 0
    // -> 0 0 0 0 0 0 1 0
    // -> 0 0 0 0 1 0 0 0
    // -> 0 0 0 1 0 0 0 0
    int rightOne;
    while (cur != 0)
    {
      rightOne = cur & -cur;
      if ((s & rightOne) == 0)
      {
        ans = (ans + f2(arr, m, n, i + 1, s | rightOne, dp)) % MOD;
      }
      cur ^= rightOne;
    }
    dp[i][s] = ans;
    return ans;
  }

 public:
  int numberWays(vector<vector<int>>& hats)
  {
    // 帽子颜色的最大值
    int m = 0;
    for (auto& person : hats)
    {
      for (auto& hat : person)
      {
        m = std::max(m, hat);
      }
    }
    int n = hats.size();
    // 1 ~ m 帽子，能满足哪些人，状态信息 -> int
    // 下标是帽子编号，值的每一bit位表示是哪个人
    vector<int> arr(m + 1);
    for (int i = 0; i < n; i++)
    {
      for (int hat : hats[i])
      {
        arr[hat] |= 1 << i;
      }
    }
    vector<vector<int>> dp(m + 1, vector<int>(1 << n, -1));
    return f1(arr, m, n, 1, 0, dp);
  }
};
