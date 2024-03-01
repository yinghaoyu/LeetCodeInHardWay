#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/all-paths-from-source-to-target/
// @sa Problem_0797_allPathsSourceTarget.cc
class Solution
{
 public:
  void f(vector<vector<int>>& graph, int cur, vector<int>& path, vector<vector<int>>& ans)
  {
    if (cur == graph.size() - 1)
    {
      ans.push_back(path);
      return;
    }
    for (auto& next : graph[cur])
    {
      path.push_back(next);
      f(graph, next, path, ans);
      path.pop_back();
    }
  }

  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
  {
    vector<int> path;
    path.push_back(0);
    vector<vector<int>> ans;
    f(graph, 0, path, ans);
    return ans;
  }
};
