#include <vector>

using namespace std;

// TODO: figure it out
class Solution
{
 public:
  // 贪心分析 + 窗口优化，只用有限几个变量维护窗口信息，无需单调队列/单调栈
  int boxDelivering(vector<vector<int>>& boxes, int portsCount, int maxBoxes, int maxWeight)
  {
    int n = boxes.size();
    // dp[i] : 马车拉完前i个货物并回仓库，需要的最少行程
    // 注意这里的i是指个数，对应的货物是boxes[0...i-1]
    vector<int> dp(n + 1);
    dp[1] = 2;
    // 马车最后一趟的货物范围[l...r]
    // 最后一趟货物的总重量weight，最后一趟需要的行程trip
    int weight = boxes[0][1];
    int trip = 2;
    for (int l = 0, r = 1; r < n; r++)
    {
      weight += boxes[r][1];
      if (boxes[r][0] != boxes[r - 1][0])
      {
        trip++;
      }
      // 1) 最后一趟货物的个数超了，最后一趟不得不减少货物
      // 2) 最后一趟货物的总重量超了，最后一趟不得不减少货物
      // 3) 最后一趟最左侧的货，分给之前的过程，如果发现之前过程的dp值没变化，那就分出去
      // 最后一趟最左侧的货，分给之前的过程，如果发现之前过程的dp值增加了，一定不要分出去
      // 对于这个逻辑，课上进行了重点图解
      while (r - l + 1 > maxBoxes || weight > maxWeight || dp[l] == dp[l + 1])
      {
        weight -= boxes[l++][1];
        if (boxes[l][0] != boxes[l - 1][0])
        {
          trip--;
        }
      }
      dp[r + 1] = dp[l] + trip;
    }
    return dp[n];
  }
};
