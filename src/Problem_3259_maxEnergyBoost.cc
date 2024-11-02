#include <vector>

using namespace std;

class Solution
{
 public:
  // TODO: 空间优化
  long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB)
  {
    int n = energyDrinkA.size();
    // dp[i][0]表示第 i 步从A取可以获得的最大值
    // dp[i][1]表示第 i 步从B取可以获得的最大值
    vector<vector<long long>> dp(n + 1, vector<long long>(2));
    // base case
    dp[1][0] = energyDrinkA[0];
    dp[1][1] = energyDrinkB[0];

    for (int i = 2; i <= n; i++)
    {
      // 要切换时，只能间隔一次取
      dp[i][0] = std::max(dp[i - 1][0], dp[i - 2][1]) + energyDrinkA[i - 1];
      dp[i][1] = std::max(dp[i - 1][1], dp[i - 2][0]) + energyDrinkB[i - 1];
    }

    return std::max(dp[n][0], dp[n][1]);
  }
};
