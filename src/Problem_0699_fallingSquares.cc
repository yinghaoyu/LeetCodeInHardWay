#include <stdint.h>
#include <algorithm>
#include <vector>

using namespace std;

// 线段树
// @sa https://www.bilibili.com/video/BV12i421X76h/
class Solution
{
 public:
  static const int MAXN = 2001;

  vector<int> arr = vector<int>(MAXN);

  vector<int> max = vector<int>(MAXN << 2);

  vector<int> change = vector<int>(MAXN << 2);

  vector<bool> updating = vector<bool>(MAXN << 2);

  // 离散化
  // 在线段树中，一般需要开4*n的空间
  // 针对 [2, 5] [3, 120] [6, 5001] 3个区间，如果开出4*5001空间，明显浪费内存
  // 可以把区间边界排序去重 2 3 5 6 120 5001，然后再定义下标映射
  // 比如 2 3 5 6 120 5001
  //      1 2 3 4  5   6
  // 下标从1开始，这样只需要开4*6的空间，这就是离散化
  int collect(vector<vector<int>>& poss)
  {
    int size = 1;
    for (auto& pos : poss)
    {
      arr[size++] = pos[0];
      arr[size++] = pos[0] + pos[1] - 1;
    }
    // 排序
    std::sort(arr.begin() + 1, arr.begin() + size);
    // 去重
    int n = 1;
    for (int i = 2; i < size; i++)
    {
      if (arr[n] != arr[i])
      {
        arr[++n] = arr[i];
      }
    }
    return n;
  }

  int rank(int n, int v)
  {
    int ans = 0;
    int l = 1, r = n, m;
    while (l <= r)
    {
      m = (l + r) >> 1;
      if (arr[m] >= v)
      {
        ans = m;
        r = m - 1;
      }
      else
      {
        l = m + 1;
      }
    }
    return ans;
  }

  void up(int i) { max[i] = std::max(max[i << 1], max[i << 1 | 1]); }

  void down(int i)
  {
    if (updating[i])
    {
      lazy(i << 1, change[i]);
      lazy(i << 1 | 1, change[i]);
      updating[i] = false;
    }
  }

  void lazy(int i, int v)
  {
    updating[i] = true;
    change[i] = v;
    max[i] = v;
  }

  void build(int l, int r, int i)
  {
    if (l < r)
    {
      int mid = (l + r) >> 1;
      build(l, mid, i << 1);
      build(mid + 1, r, i << 1 | 1);
    }
    max[i] = 0;
    change[i] = 0;
    updating[i] = false;
  }

  void update(int jobl, int jobr, int jobv, int l, int r, int i)
  {
    if (jobl <= l && r <= jobr)
    {
      lazy(i, jobv);
    }
    else
    {
      int mid = (l + r) >> 1;
      down(i);
      if (jobl <= mid)
      {
        update(jobl, jobr, jobv, l, mid, i << 1);
      }
      if (jobr > mid)
      {
        update(jobl, jobr, jobv, mid + 1, r, i << 1 | 1);
      }
      up(i);
    }
  }

  int query(int jobl, int jobr, int l, int r, int i)
  {
    if (jobl <= l && r <= jobr)
    {
      return max[i];
    }
    int mid = (l + r) >> 1;
    down(i);
    int ans = INT32_MIN;
    if (jobl <= mid)
    {
      ans = std::max(ans, query(jobl, jobr, l, mid, i << 1));
    }
    if (jobr > mid)
    {
      ans = std::max(ans, query(jobl, jobr, mid + 1, r, i << 1 | 1));
    }
    return ans;
  }

  vector<int> fallingSquares(vector<vector<int>>& pos)
  {
    // 收集所有方块左右边界
    // 去重数值 n 个
    int n = collect(pos);
    build(1, n, 1);
    vector<int> ans;
    int max = 0, l, r, h;
    for (auto& square : pos)
    {
      // 查出方块左离散后在线段树的下标
      l = rank(n, square[0]);
      // 查出方块右离散后在线段树的下标
      // 注意这里取 square[1] - 1，是为了应对方块贴边的情况
      // 比如在区间 [3,5] 增加一个2高度方块，[5, 8] 增加一个3高度方块
      // 两个方块刚好贴边落下，对于边界5来说，最大高度即不能是2也不能是3，冲突了
      // 所以在线段树内区间进行左闭右开处理，[3, 4]最大高度设为2， [6, 8]最大高度设为3
      r = rank(n, square[0] + square[1] - 1);
      // 得到每次落下方块的高度
      h = query(l, r, 1, n, 1) + square[1];
      // 收集答案
      max = std::max(max, h);
      ans.push_back(max);
      // 更新这个区间的高度
      update(l, r, h, 1, n, 1);
    }
    return ans;
  }
};
