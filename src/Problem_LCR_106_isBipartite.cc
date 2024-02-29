#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/is-graph-bipartite/
// @sa Problem_0785_isBipartite.cc
class Solution
{
 public:
  enum
  {
    UNCOLOR,
    RED,
    GREEN,
  };

  bool dfs(int node, int color, vector<int>& visited, vector<vector<int>>& graph)
  {
    if (visited[node] != UNCOLOR)
    {
      // 如果要染的节点已经被染色了，那么应该与本次要染的颜色相同
      // 否则说明不能被正确染色
      return visited[node] == color;
    }
    visited[node] = color;
    int rcolor = (color == RED ? GREEN : RED);
    // 给相邻的节点染成相反的颜色，表示选入另一个集合
    for (int next : graph[node])
    {
      if (!dfs(next, rcolor, visited, graph))
      {
        return false;
      }
    }
    return true;
  }

  // 染色法
  bool isBipartite(vector<vector<int>>& graph)
  {
    int n = graph.size();
    vector<int> visited(n, UNCOLOR);
    for (int i = 0; i < n; i++)
    {
      // 选出末染色的节点，染成红色，表示选入集合A
      if (visited[i] == UNCOLOR && !dfs(i, RED, visited, graph))
      {
        return false;
      }
    }
    return true;
  }
};
