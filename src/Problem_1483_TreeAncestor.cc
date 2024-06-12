#include <vector>

using namespace std;

// TODO: figure it out.
class TreeAncestor
{
 public:
  static const int MAXN = 50001;

  static const int LIMIT = 16;

  // 根据节点个数n，计算出2的几次方就够用了
  int power;

  int log2(int n)
  {
    int ans = 0;
    while ((1 << ans) <= (n >> 1))
    {
      ans++;
    }
    return ans;
  }

  // 链式前向星建图
  vector<int> head = vector<int>(MAXN);

  vector<int> next = vector<int>(MAXN);

  vector<int> to = vector<int>(MAXN);

  int cnt;

  // deep[i] : 节点i在第几层
  vector<int> deep = vector<int>(MAXN);

  // stjump[i][p] : 节点i往上跳2的p次方步，到达的节点编号
  vector<vector<int>> stjump = vector<vector<int>>(MAXN, vector<int>(LIMIT));

  TreeAncestor(int n, vector<int>& parent)
  {
    power = log2(n);
    cnt = 1;
    std::fill(head.begin(), head.begin() + n, 0);
    for (int i = 1; i < parent.size(); i++)
    {
      addEdge(parent[i], i);
    }
    dfs(0, 0);
  }

  void addEdge(int u, int v)
  {
    next[cnt] = head[u];
    to[cnt] = v;
    head[u] = cnt++;
  }

  // 当前来到i节点，i节点父亲节点是f
  void dfs(int i, int f)
  {
    if (i == 0)
    {
      deep[i] = 1;
    }
    else
    {
      deep[i] = deep[f] + 1;
    }
    stjump[i][0] = f;
    for (int p = 1; p <= power; p++)
    {
      stjump[i][p] = stjump[stjump[i][p - 1]][p - 1];
    }
    for (int e = head[i]; e != 0; e = next[e])
    {
      dfs(to[e], i);
    }
  }

  int getKthAncestor(int i, int k)
  {
    if (deep[i] <= k)
    {
      return -1;
    }
    // s是想要去往的层数
    int s = deep[i] - k;
    for (int p = power; p >= 0; p--)
    {
      if (deep[stjump[i][p]] >= s)
      {
        i = stjump[i][p];
      }
    }
    return i;
  }
};
