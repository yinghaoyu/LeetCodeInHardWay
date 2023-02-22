#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // TODO: figure it out
  int canCompleteCircuit1(vector<int> &gas, vector<int> &cost)
  {
    vector<bool> good = goodArray(gas, cost);
    for (int i = 0; i < gas.size(); i++)
    {
      if (good[i])
      {
        return i;
      }
    }
    return -1;
  }

  vector<bool> goodArray(vector<int> &g, vector<int> &c)
  {
    int N = g.size();
    int M = N << 1;
    vector<int> arr(M);
    for (int i = 0; i < N; i++)
    {
      arr[i] = g[i] - c[i];
      arr[i + N] = g[i] - c[i];
    }
    for (int i = 1; i < M; i++)
    {
      arr[i] += arr[i - 1];
    }
    deque<int> w;
    for (int i = 0; i < N; i++)
    {
      while (!w.empty() && arr[w.back()] >= arr[i])
      {
        w.pop_back();
      }
      w.push_back(i);
    }
    vector<bool> ans(N);
    for (int offset = 0, i = 0, j = N; j < M; offset = arr[i++], j++)
    {
      if (arr[w.front()] - offset >= 0)
      {
        ans[i] = true;
      }
      if (w.front() == i)
      {
        w.pop_front();
      }
      while (!w.empty() && arr[w.back()] >= arr[j])
      {
        w.pop_back();
      }
      w.push_back(j);
    }
    return ans;
  }

  // 这个方法的时间复杂度O(N)，额外空间复杂度O(1) 训练营讲了
  int canCompleteCircuit2(vector<int> &gas, vector<int> &cost)
  {
    if (gas.size() == 0)
    {
      return -1;
    }
    if (gas.size() == 1)
    {
      return gas[0] < cost[0] ? -1 : 0;
    }
    vector<bool> good = stations(cost, gas);
    for (int i = 0; i < gas.size(); i++)
    {
      if (good[i])
      {
        return i;
      }
    }
    return -1;
  }

  vector<bool> stations(vector<int> &cost, vector<int> &gas)
  {
    if (cost.size() < 2 || cost.size() != gas.size())
    {
      return {};
    }
    int init = changeDisArrayGetInit(cost, gas);
    return init == -1 ? vector<bool>(cost.size()) : enlargeArea(cost, init);
  }

  int changeDisArrayGetInit(vector<int> &dis, vector<int> &oil)
  {
    int init = -1;
    for (int i = 0; i < dis.size(); i++)
    {
      dis[i] = oil[i] - dis[i];
      if (dis[i] >= 0)
      {
        init = i;
      }
    }
    return init;
  }

  vector<bool> enlargeArea(vector<int> &dis, int init)
  {
    vector<bool> res(dis.size());
    int start = init;
    int end = nextIndex(init, dis.size());
    int need = 0;
    int rest = 0;
    do
    {
      // 当前来到的start已经在连通区域中，可以确定后续的开始点一定无法转完一圈
      if (start != init && start == lastIndex(end, dis.size()))
      {
        break;
      }
      // 当前来到的start不在连通区域中，就扩充连通区域
      if (dis[start] < need)
      {  // 当前start无法接到连通区的头部
        need -= dis[start];
      }
      else
      {  // 当前start可以接到连通区的头部，开始扩充连通区域的尾巴
        rest += dis[start] - need;
        need = 0;
        while (rest >= 0 && end != start)
        {
          rest += dis[end];
          end = nextIndex(end, dis.size());
        }
        // 如果连通区域已经覆盖整个环，当前的start是良好出发点，进入2阶段
        if (rest >= 0)
        {
          res[start] = true;
          connectGood(dis, lastIndex(start, dis.size()), init, res);
          break;
        }
      }
      start = lastIndex(start, dis.size());
    } while (start != init);
    return res;
  }

  // 已知start的next方向上有一个良好出发点
  // start如果可以达到这个良好出发点，那么从start出发一定可以转一圈
  void connectGood(vector<int> &dis, int start, int init, vector<bool> &res)
  {
    int need = 0;
    while (start != init)
    {
      if (dis[start] < need)
      {
        need -= dis[start];
      }
      else
      {
        res[start] = true;
        need = 0;
      }
      start = lastIndex(start, dis.size());
    }
  }

  int lastIndex(int index, int size) { return index == 0 ? (size - 1) : index - 1; }

  int nextIndex(int index, int size) { return index == size - 1 ? 0 : (index + 1); }
};

void testCanCompleteCircuit()
{
  Solution s;
  vector<int> g1 = {1, 2, 3, 4, 5};
  vector<int> c1 = {3, 4, 5, 1, 2};

  vector<int> g2 = {2, 3, 4};
  vector<int> c2 = {3, 4, 3};
  EXPECT_EQ_INT(3, s.canCompleteCircuit1(g1, c1));
  EXPECT_EQ_INT(-1, s.canCompleteCircuit1(g2, c2));
  EXPECT_EQ_INT(3, s.canCompleteCircuit2(g1, c1));
  EXPECT_EQ_INT(-1, s.canCompleteCircuit2(g2, c2));
  EXPECT_SUMMARY;
}

int main()
{
  testCanCompleteCircuit();
  return 0;
}
