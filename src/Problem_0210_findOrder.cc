#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  // 拓扑排序
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
  {
    vector<vector<int>> g(numCourses);
    vector<int> indegree(numCourses);
    for (auto& e : prerequisites)
    {
      g[e[1]].push_back(e[0]);
      indegree[e[0]]++;
    }
    queue<int> q;
    for (int i = 0; i < numCourses; i++)
    {
      if (indegree[i] == 0)
      {
        q.push(i);
      }
    }

    vector<int> ans;

    while (!q.empty())
    {
      int cur = q.front();
      q.pop();
      ans.push_back(cur);
      for (int next : g[cur])
      {
        if (--indegree[next] == 0)
        {
          q.push(next);
        }
      }
    }
    // 注意这里要检查是否所有课程都在拓扑排序中
    return ans.size() == numCourses ? ans : vector<int>{};
  }
};
