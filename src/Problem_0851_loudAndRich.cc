#include <queue>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet)
  {
    int n = quiet.size();
    vector<vector<int>> graph(n);
    vector<int> indegree(n);
    for (auto& r : richer)
    {
      graph[r[0]].push_back(r[1]);
      indegree[r[1]]++;
    }
    queue<int> que;
    for (int i = 0; i < n; i++)
    {
      if (indegree[i] == 0)
      {
        que.push(i);
      }
    }
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
    {
      ans[i] = i;
    }
    while (!que.empty())
    {
      int cur = que.front();
      que.pop();
      for (int next : graph[cur])
      {
        if (quiet[ans[cur]] < quiet[ans[next]])
        {
          ans[next] = ans[cur];
        }
        if (--indegree[next] == 0)
        {
          que.push(next);
        }
      }
    }
    return ans;
  }
};
