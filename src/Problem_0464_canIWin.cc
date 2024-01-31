#include <vector>

using namespace std;

class Solution
{
 private:
  // 如果1~7范围的数字都能选，那么status的状态为：
  // 1 1 1 1 1 1 1 1
  // 7 6 5 4 3 2 1 0
  // 0位弃而不用
  // 如果1~7范围的数字，4、2已经选了不能再选，那么status的状态为：
  // 1 1 1 0 1 0 1 1
  // 7 6 5 4 3 2 1 0
  // 0位弃而不用
  // f的含义 :
  // 数字范围1~n，当前的先手，面对status给定的数字状态
  // 在累加和还剩rest的情况下
  // 返回当前的先手能不能赢，能赢返回true，不能赢返回false
  bool f(int n, int status, int rest, vector<int>& dp)
  {
    if (rest <= 0)
    {
      return false;
    }
    if (dp[status] != 0)
    {
      return dp[status] == 1;
    }
    // rest > 0
    bool ans = false;
    for (int i = 1; i <= n; i++)
    {
      // 考察所有数字，但是不能选择之前选了的数字
      // 取 !f(args...) 表示另一个人失败了，那么我就赢了
      if ((status & (1 << i)) != 0 && !f(n, (status | (1 << i)), rest - i, dp))
      {
        ans = true;
        break;
      }
    }
    dp[status] = ans ? 1 : -1;
    return ans;
  }

 public:
  // 整数池中可选择的最大数 m
  // 累计和 n
  bool canIWin(int n, int m)
  {
    if (m == 0)
    {
      // 题设条件
      return true;
    }
    if (n * (n + 1) / 2 < m)
    {
      // 如果1~n数字全加起来
      // 累加和和是n * (n+1) / 2，都小于m
      // 那么不会有赢家，也就意味着先手不会获胜
      return false;
    }
    // dp[status] == 0 代表没算过
    // dp[status] == 1 算过，答案是true
    // dp[status] == -1 算过，答案是false
    vector<int> dp(1 << (n + 1));
    return f(n, (1 << (n + 1)) - 1, m, dp);
  }
};
