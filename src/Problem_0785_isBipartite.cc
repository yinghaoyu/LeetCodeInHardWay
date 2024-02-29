#include <queue>
#include <vector>

using namespace std;

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
  bool isBipartite1(vector<vector<int>>& graph)
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

  // bfs
  bool isBipartite2(vector<vector<int>>& graph)
  {
    int n = graph.size();
    vector<int> visited(n, UNCOLOR);
    queue<int> q;
    for (int i = 0; i < n; i++)
    {
      if (visited[i] != UNCOLOR)
      {
        continue;
      }
      q.push(i);
      visited[i] = RED;
      while (!q.empty())
      {
        int v = q.front();
        q.pop();
        for (int w : graph[v])
        {
          if (visited[w] == visited[v])
          {
            return false;
          }
          if (visited[w] == UNCOLOR)
          {
            visited[w] = visited[v] == RED ? GREEN : RED;
            q.push(w);
          }
        }
      }
    }
    return true;
  }

  bool isBipartite3(vector<vector<int>>& graph)
  {
    int n = graph.size();
    UnionFind uf(n);
    // 遍历每个顶点，将当前顶点的所有邻接点进行合并
    for (int i = 0; i < n; i++)
    {
      vector<int> nexts = graph[i];
      for (int w : graph[i])
      {
        if (uf.isConnected(i, w))
        {
          // 若某个邻接点与当前顶点已经在一个集合中了，说明不是二分图，返回 false
          return false;
        }
        uf.unions(w, nexts[0]);
      }
    }
    return true;
  }

  class UnionFind
  {
   public:
    vector<int> father;

    UnionFind(int n)
    {
      father.resize(n);
      for (int i = 0; i < n; i++)
      {
        father[i] = i;
      }
    }

    int find(int i)
    {
      if (father[i] != i)
      {
        father[i] = find(father[i]);
      }
      return father[i];
    }

    bool isConnected(int p, int q) { return find(p) == find(q); }

    void unions(int p, int q) { father[find(p)] = find(q); }
  };
};
