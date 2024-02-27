#include <functional>
#include <vector>

using namespace std;

// https://leetcode.cn/problems/count-valid-paths-in-a-tree/solutions/2456716/tu-jie-on-xian-xing-zuo-fa-pythonjavacgo-tjz2
// TODO: figure it out.

const int MX = 1e5;
bool np[MX + 1];  // 质数=false 非质数=true
// 埃氏筛
int init = []()
{
  np[1] = true;
  for (int i = 2; i * i <= MX; i++)
  {
    // 如果 i 是质数，那么 2i、3i、4i ... 都是非质数
    if (!np[i])
    {
      // 从 i * i 开始标记，因为 2i、3i ...这些数一定在 xxx
      // 之前就被其他数的倍数标记过了，例如 2 的所有倍数，3 的所有倍数等

      for (int j = i * i; j <= MX; j += i)
      {
        np[j] = true;
      }
    }
  }
  return 0;
}();

class Solution
{
 public:
  long long countPaths(int n, vector<vector<int>>& edges)
  {
    vector<vector<int>> g(n + 1);
    // 建图
    for (auto& e : edges)
    {
      int x = e[0], y = e[1];
      g[x].push_back(y);
      g[y].push_back(x);
    }

    vector<int> size(n + 1);
    vector<int> nodes;
    function<void(int, int)> dfs = [&](int x, int fa)
    {
      nodes.push_back(x);
      for (int y : g[x])
      {
        if (y != fa && np[y])
        {
          dfs(y, x);
        }
      }
    };

    long long ans = 0;
    for (int x = 1; x <= n; x++)
    {
      if (np[x])
      {
        // 跳过非质数
        continue;
      }
      int sum = 0;
      for (int y : g[x])
      {
        // 质数 x 把这棵树分成了若干个连通块
        if (!np[y])
        {
          continue;
        }
        if (size[y] == 0)
        {
          // 尚未计算过
          nodes.clear();
          // 遍历 y 所在连通块，在不经过质数的前提下，统计有多少个非质数
          dfs(y, -1);
          for (int z : nodes)
          {
            size[z] = nodes.size();
          }
        }
        // 这 size[y] 个非质数与之前遍历到的 sum 个非质数，两两之间的路径只包含质数 x
        ans += (long long) size[y] * sum;
        sum += size[y];
      }
      // 从 x 出发的路径
      ans += sum;
    }
    return ans;
  }
};
