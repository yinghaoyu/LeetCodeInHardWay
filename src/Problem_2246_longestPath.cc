#include <functional>
#include <string>
#include <vector>

using namespace std;

// 树型dp
// https://leetcode.cn/problems/longest-path-with-different-adjacent-characters/solutions/1427611/by-endlesscheng-92fw/
class Solution
{
 public:
  int longestPath(vector<int>& parent, string s)
  {
    int n = parent.size();
    vector<vector<int>> g(n);
    for (int i = 1; i < n; ++i)
    {
      g[parent[i]].push_back(i);
    }

    int ans = 0;
    function<int(int)> dfs = [&](int x) -> int
    {
      // 必须以 x 开头往下的路径最长长度
      int maxLen = 0;
      for (int y : g[x])
      {
        // 必须以 y 开头往下的路径最长长度 + 边(x -> y)长度 1
        int len = dfs(y) + 1;
        if (s[y] != s[x])
        {
          // 枚举更新以 x 为根，左右两条路径和的最大值
          ans = max(ans, maxLen + len);
          maxLen = max(maxLen, len);
        }
      }
      return maxLen;
    };
    dfs(0);
    return ans + 1;
  }
};
