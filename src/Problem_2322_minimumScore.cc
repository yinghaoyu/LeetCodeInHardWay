#include <algorithm>
#include <vector>

using namespace std;

// dfn序号
// @sa Problem_2458_treeQueries.cc
// @sa https://www.bilibili.com/video/BV1ae411f7AC/
class Solution
{
 private:
  static constexpr int MAXN = 1001;

  // 下标为原始节点编号
  int dfn[MAXN];

  // 下标为dfn序号
  int XOR[MAXN];

  // 下标为dfn序号
  int size[MAXN];

  int dfnCnt;

  // 当前来到原始编号u，遍历u的整棵树
  void f(vector<int>& nums, vector<vector<int>>& graph, int u)
  {
    int i = ++dfnCnt;
    dfn[u] = i;
    XOR[i] = nums[u];
    size[i] = 1;
    for (int v : graph[u])
    {
      // dfn[v] == 0 说明没分配过
      if (dfn[v] == 0)
      {
        f(nums, graph, v);
        XOR[i] ^= XOR[dfn[v]];
        size[i] += size[dfn[v]];
      }
    }
  }

 public:
  int minimumScore(vector<int>& nums, vector<vector<int>>& edges)
  {
    int n = nums.size();
    vector<vector<int>> graph(n);
    for (auto& edge : edges)
    {
      graph[edge[0]].push_back(edge[1]);
      graph[edge[1]].push_back(edge[0]);
    }
    std::fill_n(dfn, n, 0);
    dfnCnt = 0;
    f(nums, graph, 0);
    int m = edges.size();
    int ans = INT32_MAX;
    // 枚举所有边
    for (int i = 0, a, b, pre, pos, sum1, sum2, sum3; i < m; i++)
    {
      a = std::max(dfn[edges[i][0]], dfn[edges[i][1]]);
      for (int j = i + 1; j < m; j++)
      {
        b = std::max(dfn[edges[j][0]], dfn[edges[j][1]]);
        if (a < b)
        {
          pre = a;
          pos = b;
        }
        else
        {
          pre = b;
          pos = a;
        }
        sum1 = XOR[pos];
        // xor[1] : 整棵树的异或和
        // 因为头节点是0，一定拥有最小的dfn序号1
        // f函数调用的时候，也是从0节点开始的
        if (pos < pre + size[pre])
        {
          // pos 是 pre 的子树节点
          sum2 = XOR[pre] ^ XOR[pos];
          sum3 = XOR[1] ^ XOR[pre];
        }
        else
        {
          // pos 不是 pre 的子树节点
          sum2 = XOR[pre];
          sum3 = XOR[1] ^ sum1 ^ sum2;
        }
        ans = std::min(ans, std::max({sum1, sum2, sum3}) - std::min({sum1, sum2, sum3}));
      }
    }
    return ans;
  }
};
