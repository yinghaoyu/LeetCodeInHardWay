#include <algorithm>
#include <queue>
#include <string>
#include <vector>

using namespace std;

// @sa https://www.bilibili.com/video/BV1rj411k7tS/
// 抽象的拓扑排序题
class Solution
{
 public:
  vector<int> movesToStamp(string stamp, string target)
  {
    int m = stamp.length();
    int n = target.length();
    // 为什么这里只需要 n - m + 1 ?
    // 因为贴邮票时，邮票开头只能在 [0, n - m] 区间内开贴，后面的m长度需要保留，不能截断邮票
    // 开始时，有m个字符，假设都是错误的，那么入度为m
    // 如果都是对的字符，那么入度为0，入度为0一定是最后贴上去的
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
      // cur 是贴邮票的开始位置，那么需要检查m长度整张邮票的位置
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
      // TODO: 这里为什么要判断 size ？
      return vector<int>();
    }
    std::reverse(path.begin(), path.end());
    return path;
  }
};
