#include <functional>
#include <string>
#include <vector>

using namespace std;

// TODO: figure it out.
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
      int maxLen = 0;
      for (int y : g[x])
      {
        int len = dfs(y) + 1;
        if (s[y] != s[x])
        {
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
