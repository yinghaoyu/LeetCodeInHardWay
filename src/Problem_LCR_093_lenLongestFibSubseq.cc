#include <unordered_map>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/length-of-longest-fibonacci-subsequence/
// @sa Problem_0873_lenLongestFibSubseq.cc
class Solution
{
 public:
  int lenLongestFibSubseq(vector<int>& arr)
  {
    int n = arr.size();
    unordered_map<int, int> map;
    int ans = 0;
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; i++)
    {
      map[arr[i]] = i;
    }
    for (int i = 0; i < n - 1; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        dp[i][j] = std::max(dp[i][j], 2);
        int next = arr[i] + arr[j];
        if (map.count(next))
        {
          int k = map[next];
          dp[j][k] = dp[i][j] + 1;
          ans = std::max(ans, dp[j][k]);
        }
      }
    }
    return ans;
  }
};
