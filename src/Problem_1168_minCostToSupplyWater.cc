#include <algorithm>
#include <vector>

using namespace std;

// 水资源分配优化
// 村里面一共有 n 栋房子。我们希望通过建造水井和铺设管道来为所有房子供水。
// 对于每个房子 i，我们有两种可选的供水方案：一种是直接在房子内建造水井
// 成本为 wells[i - 1] （注意 -1 ，因为 索引从0开始 ）
// 另一种是从另一口井铺设管道引水，数组 pipes 给出了在房子间铺设管道的成本，
// 其中每个 pipes[j] = [house1j, house2j, costj]
// 代表用管道将 house1j 和 house2j连接在一起的成本。连接是双向的。
// 请返回 为所有房子都供水的最低总成本
// @sa https://www.bilibili.com/video/BV1sK4y1F7LH/
class OptimizeWaterDistribution
{
 public:
  int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes)
  {
    build(n);
    // 虚拟一个0点，0点到每个点的距离是直接铺管道的成本
    for (int i = 0; i < n; i++, cnt++)
    {
      // wells : 100   30
      //         0(1)  1(2)
      edges[cnt][0] = 0;
      edges[cnt][1] = i + 1;
      edges[cnt][2] = wells[i];
    }
    // 下面是每个村庄联通的距离
    for (int i = 0; i < pipes.size(); i++, cnt++)
    {
      edges[cnt][0] = pipes[i][0];
      edges[cnt][1] = pipes[i][1];
      edges[cnt][2] = pipes[i][2];
    }
    // 这样，转化为整张图带0点的最小生成树
    // 按边长排序，直接用Kruskal算法
    std::sort(edges.begin(), edges.end() + cnt, [](auto& a, auto& b) { return a[2] < b[2]; });
    int ans = 0;
    for (int i = 0; i < cnt; i++)
    {
      if (unions(edges[i][0], edges[i][1]))
      {
        ans += edges[i][2];
      }
    }
    return ans;
  }

  static const int MAXN = 10010;

  vector<vector<int>> edges = vector<vector<int>>(MAXN << 1, vector<int>(3));

  int cnt;

  vector<int> father = vector<int>(MAXN);

  void build(int n)
  {
    cnt = 0;
    for (int i = 0; i <= n; i++)
    {
      father[i] = i;
    }
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }

  // 如果x和y，原本是一个集合，返回false
  // 如果x和y，不是一个集合，合并之后后返回true
  bool unions(int x, int y)
  {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy)
    {
      father[fx] = fy;
      return true;
    }
    else
    {
      return false;
    }
  }
};
