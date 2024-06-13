#include <vector>

using namespace std;

// TODO: fix it. run out of time.
class Solution
{
 public:
  static const int MAXN = 10001;

  static const int MAXM = 20001;

  static const int MAXW = 26;

  // 链式前向星建图
  vector<int> headEdge = vector<int>(MAXN);

  vector<int> edgeNext = vector<int>(MAXN << 1);

  vector<int> edgeTo = vector<int>(MAXN << 1);

  vector<int> edgeValue = vector<int>(MAXN << 1);

  int tcnt;

  // weightCnt[i][w] : 从头节点到i的路径中，权值为w的边有几条
  vector<vector<int>> weightCnt = vector<vector<int>>(MAXN, vector<int>(MAXW + 1));

  // 以下所有的结构都是为了tarjan算法做准备
  vector<int> headQuery = vector<int>(MAXN);

  vector<int> queryNext = vector<int>(MAXM << 1);

  vector<int> queryTo = vector<int>(MAXM << 1);

  vector<int> queryIndex = vector<int>(MAXM << 1);

  int qcnt;

  vector<bool> visited = vector<bool>(MAXN);

  vector<int> father = vector<int>(MAXN);

  vector<int> lca = vector<int>(MAXM);

  vector<int> minOperationsQueries(int n, vector<vector<int>>& edges, vector<vector<int>>& queries)
  {
    build(n);
    for (auto& edge : edges)
    {
      addEdge(edge[0], edge[1], edge[2]);
      addEdge(edge[1], edge[0], edge[2]);
    }
    // 从头节点到每个节点的边权值词频统计
    dfs(0, 0, -1);
    int m = queries.size();
    for (int i = 0; i < m; i++)
    {
      addQuery(queries[i][0], queries[i][1], i);
      addQuery(queries[i][1], queries[i][0], i);
    }
    // 得到每个查询的最低公共祖先
    tarjan(0, -1);
    vector<int> ans(m);
    for (int i = 0, a, b, c; i < m; i++)
    {
      a = queries[i][0];
      b = queries[i][1];
      c = lca[i];
      int allCnt = 0;  // 从a到b的路，所有权值的边一共多少条
      int maxCnt = 0;  // 从a到b的路，权值重复最多的次数
      for (int w = 1, wcnt; w <= MAXW; w++)
      {  // 所有权值枚举一遍
        wcnt = weightCnt[a][w] + weightCnt[b][w] - 2 * weightCnt[c][w];
        maxCnt = std::max(maxCnt, wcnt);
        allCnt += wcnt;
      }
      ans[i] = allCnt - maxCnt;
    }
    return ans;
  }

  void build(int n)
  {
    tcnt = qcnt = 1;
    std::fill(headEdge.begin(), headEdge.begin() + n, 0);
    std::fill(headQuery.begin(), headQuery.begin() + n, 0);
    std::fill(visited.begin(), visited.begin() + n, false);
    for (int i = 0; i < n; i++)
    {
      father[i] = i;
    }
  }

  void addEdge(int u, int v, int w)
  {
    edgeNext[tcnt] = headEdge[u];
    edgeTo[tcnt] = v;
    edgeValue[tcnt] = w;
    headEdge[u] = tcnt++;
  }

  // 当前来到u节点，父亲节点f，从f到u权重为w
  // 统计从头节点到u节点，每种权值的边有多少条
  // 信息存放在weightCnt[u][1..26]里
  void dfs(int u, int w, int f)
  {
    if (u == 0)
    {
      std::fill(weightCnt[u].begin(), weightCnt[u].end(), 0);
    }
    else
    {
      for (int i = 1; i <= MAXW; i++)
      {
        weightCnt[u][i] = weightCnt[f][i];
      }
      weightCnt[u][w]++;
    }
    for (int e = headEdge[u]; e != 0; e = edgeNext[e])
    {
      if (edgeTo[e] != f)
      {
        dfs(edgeTo[e], edgeValue[e], u);
      }
    }
  }

  void addQuery(int u, int v, int i)
  {
    queryNext[qcnt] = headQuery[u];
    queryTo[qcnt] = v;
    queryIndex[qcnt] = i;
    headQuery[u] = qcnt++;
  }

  // tarjan算法批量查询两点的最低公共祖先
  void tarjan(int u, int f)
  {
    visited[u] = true;
    for (int e = headEdge[u]; e != 0; e = edgeNext[e])
    {
      if (edgeTo[e] != f)
      {
        tarjan(edgeTo[e], u);
      }
    }
    for (int e = headQuery[u], v; e != 0; e = queryNext[e])
    {
      v = queryTo[e];
      if (visited[v])
      {
        lca[queryIndex[e]] = find(v);
      }
    }
    father[u] = f;
  }

  int find(int i)
  {
    if (i != father[i])
    {
      father[i] = find(father[i]);
    }
    return father[i];
  }
};
