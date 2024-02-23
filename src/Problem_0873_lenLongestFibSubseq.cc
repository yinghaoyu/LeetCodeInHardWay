#include <map>
#include <vector>

using namespace std;

class Solution
{
 public:
  int lenLongestFibSubseq(vector<int>& arr)
  {
    int n = arr.size();
    int ans = 0;
    map<int, int> map;
    for (int i = 0; i < n; i++)
    {
      // 记录 {value, index}
      map[arr[i]] = i;
    }
    vector<vector<int>> dp(n, vector<int>(n));
    // 先固定前面两个数arr[i] arr[j]，找 arr[k]
    for (int i = 0; i < n - 1; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        dp[i][j] = std::max(dp[i][j], 2);
        int next = arr[i] + arr[j];
        if (map.count(next))
        {
          // 根据题设，arr是单调递增的，所以一定有 k > j
          int k = map[next];
          dp[j][k] = dp[i][j] + 1;
          ans = std::max(ans, dp[j][k]);
        }
      }
    }
    return ans;
  }
};
