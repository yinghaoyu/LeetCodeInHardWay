#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 private:
  static constexpr int MAXN = 13;

  vector<int> getDebts(vector<vector<int>>& transactions)
  {
    vector<int> help(MAXN);
    for (auto& t : transactions)
    {
      help[t[0]] -= t[2];
      help[t[1]] += t[2];
    }
    int n = 0;
    for (int num : help)
    {
      if (num != 0)
      {
        n++;
      }
    }
    vector<int> debt(n);
    int index = 0;
    for (int num : help)
    {
      if (num != 0)
      {
        debt[index++] = num;
      }
    }
    return debt;
  }

  int f(vector<int>& debt, int set, int sum, int n, vector<int>& dp)
  {
    if (dp[set] != -1)
    {
      return dp[set];
    }
    int ans = 0;
    // 集合中不只一个元素
    if ((set & set - 1) != 0)
    {
      if (sum == 0)
      {
        for (int i = 0; i < n; i++)
        {
          if ((set & (1 << i)) != 0)
          {
            // 找到任何一个元素，去除这个元素
            // 剩下的集合进行尝试，返回值 + 1
            ans = f(debt, set ^ (1 << i), sum - debt[i], n, dp) + 1;
            // 然后不需要再尝试下一个元素了，因为答案一定是一样的
            // 所以直接break
            break;
          }
        }
      }
    }
    else
    {
      for (int i = 0; i < n; i++)
      {
        if ((set & (1 << i)) != 0)
        {
          ans = std::max(ans, f(debt, set ^ (1 << i), sum - debt[i], n, dp));
        }
      }
    }
    dp[set] = ans;
    return ans;
  }

 public:
  int minTransfers(vector<vector<int>>& transactions)
  {
    // 加工出来的debt数组中一定不含有0
    vector<int> debt = getDebts(transactions);
    int n = debt.size();
    vector<int> dp(1 << n, -1);
    return n - f(debt, (1 << n) - 1, 0, n, dp);
  }
};
