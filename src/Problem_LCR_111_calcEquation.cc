#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/evaluate-division/
// @sa Problem_0399_calcEquation.cc

class Solution
{
 public:
  vector<double> calcEquation(vector<vector<string>>& equations,
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
      if (!variables.count(q[0]) && !variables.count(q[1]))
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
};
