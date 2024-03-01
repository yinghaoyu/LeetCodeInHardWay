#include <vector>

using namespace std;

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

  // dfs
  vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
  {
    vector<int> path;
    path.push_back(0);
    vector<vector<int>> ans;
    f(graph, 0, path, ans);
    return ans;
  }
};
