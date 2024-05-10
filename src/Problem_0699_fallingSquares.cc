#include <stdint.h>
#include <algorithm>
#include <vector>

using namespace std;

// 线段树
// TODO: figure it out.
class Solution
{
 public:
  static const int MAXN = 2001;

  vector<int> arr = vector<int>(MAXN);

  vector<int> max = vector<int>(MAXN << 2);

  vector<int> change = vector<int>(MAXN << 2);

  vector<bool> __update = vector<bool>(MAXN << 2);

  int collect(vector<vector<int>>& poss)
  {
    int size = 1;
    for (auto& pos : poss)
    {
      arr[size++] = pos[0];
      arr[size++] = pos[0] + pos[1] - 1;
    }
    std::sort(arr.begin() + 1, arr.begin() + size);
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
    if (__update[i])
    {
      lazy(i << 1, change[i]);
      lazy(i << 1 | 1, change[i]);
      __update[i] = false;
    }
  }

  void lazy(int i, int v)
  {
    __update[i] = true;
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
    __update[i] = false;
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
    int n = collect(pos);
    build(1, n, 1);
    vector<int> ans;
    int max = 0, l, r, h;
    for (auto& square : pos)
    {
      l = rank(n, square[0]);
      r = rank(n, square[0] + square[1] - 1);
      h = query(l, r, 1, n, 1) + square[1];
      max = std::max(max, h);
      ans.push_back(max);
      update(l, r, h, 1, n, 1);
    }
    return ans;
  }
};
