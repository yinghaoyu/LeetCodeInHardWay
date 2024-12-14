#include <queue>
#include <vector>

using namespace std;

// 拓扑排序
// @sa https://www.bilibili.com/video/BV12y4y1F79q/
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
      // 拥有前不少于自己，安静值最小的人，默认是自己
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
          // cur 比 next 有钱，且 cur 收集到的答案比 next 小
          // 那么就依照拓扑排序的顺序传递更新
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
