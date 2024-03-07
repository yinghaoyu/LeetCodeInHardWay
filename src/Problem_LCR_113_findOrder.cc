#include <queue>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/course-schedule-ii/
// @sa Problem_0210_findOrder.cc
class Solution
{
 public:
  vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites)
  {
    vector<int> indegrees(numCourses);
    vector<vector<int>> graph(numCourses);
    for (auto& e : prerequisites)
    {
      graph[e[1]].push_back(e[0]);
      indegrees[e[0]]++;
    }
    queue<int> q;
    for (int i = 0; i < numCourses; i++)
    {
      if (indegrees[i] == 0)
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
      for (int next : graph[cur])
      {
        if (--indegrees[next] == 0)
        {
          q.push(next);
        }
      }
    }
    return ans.size() == numCourses ? ans : vector<int>{};
  }
};
