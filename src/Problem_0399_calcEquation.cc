#include <queue>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution
{
 public:
  // bfs
  vector<double> calcEquation1(vector<vector<string>>& equations,
                               vector<double>& values,
                               vector<vector<string>>& queries)
  {
    int vars = 0;
    // 统计节点
    unordered_map<string, int> variables;
    int n = equations.size();
    for (int i = 0; i < n; i++)
    {
      if (!variables.count(equations[i][0]))
      {
        variables[equations[i][0]] = vars++;
      }
      if (!variables.count(equations[i][1]))
      {
        variables[equations[i][1]] = vars++;
      }
    }

    // 建图
    vector<vector<std::pair<int, double>>> edges(vars);
    for (int i = 0; i < n; i++)
    {
      int idxA = variables[equations[i][0]];
      int idxB = variables[equations[i][1]];
      edges[idxA].push_back({idxB, values[i]});
      edges[idxB].push_back({idxA, 1.0 / values[i]});
    }

    vector<double> ans;
    for (auto& q : queries)
    {
      double res = -1.0;
      if (variables.count(q[0]) && variables.count(q[1]))
      {
        int idxA = variables[q[0]];
        int idxB = variables[q[1]];
        if (idxA == idxB)
        {
          res = 1.0;
        }
        else
        {
          queue<int> points;
          points.push(idxA);
          vector<double> ratios(vars, -1.0);
          ratios[idxA] = 1.0;
          while (!points.empty() && ratios[idxB] < 0)
          {
            int cur = points.front();
            points.pop();

            for (auto& [next, val] : edges[cur])
            {
              if (ratios[next] < 0)
              {
                // 没计算过的才需要计算
                // ratios数组相当于一般 bfs 的 vsisted 数组
                ratios[next] = ratios[cur] * val;
                points.push(next);
              }
            }
          }
          res = ratios[idxB];
        }
      }
      ans.push_back(res);
    }
    return ans;
  }

  // 对于查询数量很多的情形，如果为每次查询都独立搜索一次，则效率会变低。
  // 为此，我们不妨对图先做一定的预处理，随后就可以在较短的时间内回答每个查询。
  // 利用 Floyd 算法，先计算出任意两点之间的距离
  vector<double> calcEquation2(vector<vector<string>>& equations,
                               vector<double>& values,
                               vector<vector<string>>& queries)
  {
    int vars = 0;
    // 统计节点
    unordered_map<string, int> variables;
    int n = equations.size();
    for (int i = 0; i < n; i++)
    {
      if (!variables.count(equations[i][0]))
      {
        variables[equations[i][0]] = vars++;
      }
      if (!variables.count(equations[i][1]))
      {
        variables[equations[i][1]] = vars++;
      }
    }

    // 建图
    vector<vector<double>> edges(vars, vector<double>(vars, -1.0));
    for (int i = 0; i < n; i++)
    {
      int idxA = variables[equations[i][0]];
      int idxB = variables[equations[i][1]];
      edges[idxA][idxB] = values[i];
      edges[idxB][idxA] = 1.0 / values[i];
    }

    // 预处理
    for (int k = 0; k < vars; k++)
    {
      for (int i = 0; i < vars; i++)
      {
        for (int j = 0; j < vars; j++)
        {
          if (edges[i][k] > 0 && edges[k][j] > 0)
          {
            edges[i][j] = edges[i][k] * edges[k][j];
          }
        }
      }
    }

    vector<double> ans;
    for (auto& q : queries)
    {
      double res = -1.0;
      if (variables.count(q[0]) && variables.count(q[1]))
      {
        int idxA = variables[q[0]];
        int idxB = variables[q[1]];
        if (edges[idxA][idxB] > 0)
        {
          res = edges[idxA][idxB];
        }
      }
      ans.push_back(res);
    }
    return ans;
  }

  // 并查集
  vector<double> calcEquation3(vector<vector<string>>& equations,
                               vector<double>& values,
                               vector<vector<string>>& queries)
  {
    int n = equations.size();
    UnionFind uf(2 * n);
    unordered_map<string, int> map;
    int id = 0;
    for (int i = 0; i < n; i++)
    {
      string a = equations[i][0];
      string b = equations[i][1];
      if (!map.count(a))
      {
        map[a] = id;
        id++;
      }
      if (!map.count(b))
      {
        map[b] = id;
        id++;
      }
      uf.unions(map[a], map[b], values[i]);
    }

    int m = queries.size();
    vector<double> ans(m);
    for (int i = 0; i < m; i++)
    {
      string a = queries[i][0];
      string b = queries[i][1];

      if (!map.count(a) || !map.count(b))
      {
        ans[i] = -1.0;
      }
      else
      {
        int idA = map[a];
        int idB = map[b];
        ans[i] = uf.isConnected(idA, idB);
      }
    }
    return ans;
  }

  class UnionFind
  {
   private:
    vector<int> parent;
    vector<double> weight;

   public:
    UnionFind(int n)
    {
      parent.resize(n);
      weight.resize(n);
      for (int i = 0; i < n; i++)
      {
        parent[i] = i;
        weight[i] = 1.0;
      }
    }

    int find(int x)
    {
      if (x != parent[x])
      {
        int c = parent[x];
        parent[x] = find(parent[x]);
        weight[x] *= weight[c];
      }
      return parent[x];
    }

    void unions(int x, int y, double value)
    {
      int px = find(x);
      int py = find(y);
      if (px != py)
      {
        parent[px] = py;
        // TODO: 这里理解比较绕
        weight[px] = weight[y] * value / weight[x];
      }
    }

    double isConnected(int x, int y)
    {
      int px = find(x);
      int py = find(y);
      if (px == py)
      {
        return weight[x] / weight[y];
      }
      else
      {
        return -1.0;
      }
    }
  };
};
