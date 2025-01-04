#include <cstdint>
#include <vector>

using namespace std;

// Bellman-Ford算法
// @sa https://www.bilibili.com/video/BV1t94y187zW/
class Solution
{
 public:
  int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k)
  {
    vector<int> cur(n, INT32_MAX);
    cur[src] = 0;
    for (int i = 0; i <= k; i++)
    {
      // 注意：这里为何要拷贝一份数组？
      vector<int> next = cur;
      for (auto& e : flights)
      {
        // a -> b, w
        if (cur[e[0]] != INT32_MAX)
        {
          next[e[1]] = std::min(next[e[1]], cur[e[0]] + e[2]);
        }
      }
      cur = next;
    }
    return cur[dst] == INT32_MAX ? -1 : cur[dst];
  }
};
