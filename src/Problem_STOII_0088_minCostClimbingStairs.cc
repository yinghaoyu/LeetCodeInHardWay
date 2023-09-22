#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/min-cost-climbing-stairs/
// @sa Problem_0746_minCostClimbingStairs.cc

class Solution
{
 public:
  int minCostClimbingStairs(vector<int> &cost)
  {
    int n = cost.size();
    int pre = 0, cur = 0;
    for (int i = 2; i <= n; i++)
    {
      int next = std::min(cur + cost[i - 1], pre + cost[i - 2]);
      pre = cur;
      cur = next;
    }
    return cur;
  }
};
