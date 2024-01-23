#include <queue>
#include <vector>

using namespace std;

class Solution
{
 public:
  int maximumInvitations(vector<int>& favorite)
  {
    int n = favorite.size();
    vector<int> indegree(n);
    for (int i = 0; i < n; i++)
    {
      indegree[favorite[i]]++;
    }
    queue<int> que;
    for (int i = 0; i < n; i++)
    {
      if (indegree[i] == 0)
      {
        que.push(i);
      }
    }
    // deep[i] : 不包括i在内，i之前的最长链的长度
    vector<int> deep(n);
    while (!que.empty())
    {
      int cur = que.front();
      que.pop();
      int next = favorite[cur];
      deep[next] = std::max(deep[next], deep[cur] + 1);
      if (--indegree[next] == 0)
      {
        que.push(next);
      }
    }
    // 目前图中的点，不在环上的点，都删除了！ indegree[i] == 0
    // 可能性1 : 所有小环(中心个数 == 2)，算上中心点 + 延伸点，总个数
    int sumOfSmallRings = 0;
    // 可能性2 : 所有大环(中心个数 > 2)，只算中心点，最大环的中心点个数
    int bigRings = 0;
    for (int i = 0; i < n; i++)
    {
      // 只关心的环！
      if (indegree[i] > 0)
      {
        int ringSize = 1;
        indegree[i] = 0;
        for (int j = favorite[i]; j != i; j = favorite[j])
        {
          ringSize++;
          indegree[j] = 0;
        }
        if (ringSize == 2)
        {
          sumOfSmallRings += 2 + deep[i] + deep[favorite[i]];
        }
        else
        {
          bigRings = std::max(bigRings, ringSize);
        }
      }
    }
    return std::max(sumOfSmallRings, bigRings);
  }
};
