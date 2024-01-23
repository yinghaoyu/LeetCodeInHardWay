#include <queue>
#include <string>
#include <vector>

using namespace std;

// TODO: figure it out.
class Solution
{
 public:
  vector<int> movesToStamp(string stamp, string target)
  {
    int m = stamp.length();
    int n = target.length();
    vector<int> indegree(n - m + 1, m);
    vector<vector<int>> graph(n);
    queue<int> que;
    for (int i = 0; i <= n - m; i++)
    {
      // i开头....(m个)
      // i+0 i+1 i+m-1
      for (int j = 0; j < m; j++)
      {
        if (target[i + j] == stamp[j])
        {
          if (--indegree[i] == 0)
          {
            que.push(i);
          }
        }
        else
        {
          // i + j
          // from : 错误的位置
          // to : i开头的下标
          graph[i + j].push_back(i);
        }
      }
    }
    // 同一个位置取消错误不要重复统计
    vector<bool> visited(n);
    vector<int> path(n - m + 1);
    int size = 0;
    while (!que.empty())
    {
      int cur = que.front();
      que.pop();
      path[size++] = cur;
      for (int i = 0; i < m; i++)
      {
        // cur : 开头位置
        // cur + 0 cur + 1 cur + 2 ... cur + m - 1
        if (!visited[cur + i])
        {
          visited[cur + i] = true;
          for (int next : graph[cur + i])
          {
            if (--indegree[next] == 0)
            {
              que.push(next);
            }
          }
        }
      }
    }
    if (size != n - m + 1)
    {
      return vector<int>();
    }
    // path 逆序调整
    for (int i = 0, j = size - 1; i < j; i++, j--)
    {
      std::swap(path[i], path[j]);
    }
    return path;
  }
};
