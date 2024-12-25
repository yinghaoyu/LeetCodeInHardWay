#include <cstdint>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

// Prim 和 Diskstra 算法的区别：
// Prim更新的是未标记集合到已标记集合之间的距离
// Dijkstra更新的是源点到未标记集合之间的距离
// Prim是计算最小生成树的算法，比如为N个村庄修路，怎么修花销最少
// Dijkstra是计算最短路径的算法，比如从a村庄走到其他任意村庄的距离

// Dijkstra算法模版
class Solution
{
 private:
  class cmp
  {
   public:
    bool operator()(std::pair<int, int>& lhs, std::pair<int, int>& rhs)
    {
      return lhs.second > rhs.second;
    }
  };

 public:
  // 动态建图+普通堆的实现
  int networkDelayTime(vector<vector<int>>& times, int n, int k)
  {
    vector<vector<std::pair<int, int>>> graph(n + 1);
    for (auto& e : times)
    {
      graph[e[0]].push_back({e[1], e[2]});
    }
    vector<bool> visited(n + 1);
    static const int MAX = 1e6;
    vector<int> distance(n + 1, MAX);
    // 0 : 当前节点
    // 1 : 源点到当前点距离，按从小到大排序
    priority_queue<std::pair<int, int>, vector<std::pair<int, int>>, cmp> heap;
    distance[k] = 0;
    heap.push({k, 0});
    while (!heap.empty())
    {
      auto [u, _] = heap.top();
      heap.pop();
      visited[u] = true;
      for (auto& [v, w] : graph[u])
      {
        if (!visited[v] && distance[u] + w < distance[v])
        {
          distance[v] = distance[u] + w;
          heap.push({v, distance[v]});
        }
      }
    }
    int ans = INT32_MIN;
    for (int i = 1; i <= n; i++)
    {
      if (distance[i] == MAX)
      {
        return -1;
      }
      ans = std::max(ans, distance[i]);
    }
    return ans;
  }

  // 最优解
  // 链式前向星+反向索引堆的实现
  int networkDelayTime2(vector<vector<int>>& times, int n, int s)
  {
    build(n);
    for (auto& edge : times)
    {
      addEdge(edge[0], edge[1], edge[2]);
    }
    addOrUpdateOrIgnore(s, 0);
    while (!isEmpty())
    {
      int u = pop();
      for (int ei = head[u]; ei > 0; ei = next[ei])
      {
        addOrUpdateOrIgnore(to[ei], distance[u] + weight[ei]);
      }
    }
    int ans = INT32_MIN;
    for (int i = 1; i <= n; i++)
    {
      if (distance[i] == INT32_MAX)
      {
        return -1;
      }
      ans = std::max(ans, distance[i]);
    }
    return ans;
  }

  static const int MAXN = 101;

  static const int MAXM = 6001;

  // 链式前向星
  vector<int> head = vector<int>(MAXN);

  vector<int> next = vector<int>(MAXM);

  vector<int> to = vector<int>(MAXM);

  vector<int> weight = vector<int>(MAXM);

  int cnt;

  // 反向索引堆
  vector<int> heap = vector<int>(MAXN);

  // where[v] = -1，表示v这个节点，从来没有进入过堆
  // where[v] = -2，表示v这个节点，已经弹出过了
  // where[v] = i(>=0)，表示v这个节点，在堆上的i位置
  vector<int> where = vector<int>(MAXN);

  int heapSize;

  vector<int> distance = vector<int>(MAXN);

  void build(int n)
  {
    cnt = 1;
    heapSize = 0;
    std::fill(head.begin() + 1, head.begin() + n + 1, 0);
    std::fill(where.begin() + 1, where.begin() + n + 1, -1);
    std::fill(distance.begin() + 1, distance.begin() + n + 1, INT32_MAX);
  }

  // 链式前向星建图
  void addEdge(int u, int v, int w)
  {
    next[cnt] = head[u];
    to[cnt] = v;
    weight[cnt] = w;
    head[u] = cnt++;
  }

  void addOrUpdateOrIgnore(int v, int c)
  {
    if (where[v] == -1)
    {
      heap[heapSize] = v;
      where[v] = heapSize++;
      distance[v] = c;
      heapInsert(where[v]);
    }
    else if (where[v] >= 0)
    {
      distance[v] = std::min(distance[v], c);
      heapInsert(where[v]);
    }
  }

  // 反向索引堆的精髓就在于 heapInsert
  // 如果是小根堆，只允许修改的值 <= 当前的值，
  // 如果是大根堆，只允许修改的值 >= 当前的值，
  // 直接从where[i]找i在堆的位置，然后执行 heapInsert
  // 这样只需要局部向上调整堆，而不是 heapify
  void heapInsert(int i)
  {
    while (distance[heap[i]] < distance[heap[(i - 1) / 2]])
    {
      swap(i, (i - 1) / 2);
      i = (i - 1) / 2;
    }
  }

  int pop()
  {
    int ans = heap[0];
    swap(0, --heapSize);
    heapify(0);
    where[ans] = -2;
    return ans;
  }

  void heapify(int i)
  {
    int l = i * 2 + 1;
    while (l < heapSize)
    {
      int best = l + 1 < heapSize && distance[heap[l + 1]] < distance[heap[l]] ? l + 1 : l;
      best = distance[heap[best]] < distance[heap[i]] ? best : i;
      if (best == i)
      {
        break;
      }
      swap(best, i);
      i = best;
      l = i * 2 + 1;
    }
  }

  bool isEmpty() { return heapSize == 0; }

  void swap(int i, int j)
  {
    int tmp = heap[i];
    heap[i] = heap[j];
    heap[j] = tmp;
    where[heap[i]] = i;
    where[heap[j]] = j;
  }
};
