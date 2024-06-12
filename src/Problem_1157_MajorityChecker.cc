#include <algorithm>
#include <vector>

using namespace std;

// 摩尔投票 + 线段树
// TODO: figure it out. fix it.
class MajorityChecker
{
 public:
  static const int MAXN = 20001;

  vector<vector<int>> nums = vector<vector<int>>(MAXN, vector<int>(2));

  // 维护线段树一段范围，候选是谁
  vector<int> cand = vector<int>(MAXN << 2);

  // 维护线段树一段范围，候选血量
  vector<int> hp = vector<int>(MAXN << 2);

  int n;

  MajorityChecker(vector<int>& arr)
  {
    n = arr.size();
    buildCnt(arr);
    buildTree(arr, 1, n, 1);
  }

  int query(int l, int r, int t)
  {
    vector<int> ch = findCandidate(l + 1, r + 1, 1, n, 1);
    int candidate = ch[0];
    return cnt(l, r, candidate) >= t ? candidate : -1;
  }

  void buildCnt(vector<int>& arr)
  {
    for (int i = 0; i < n; i++)
    {
      nums[i][0] = arr[i];
      nums[i][1] = i;
    }
    std::sort(nums.begin(), nums.end(), [](vector<int>& a, vector<int>& b)
              { return a[0] != b[0] ? a[0] > b[0] : a[1] > b[1]; });
  }

  int cnt(int l, int r, int v) { return bs(v, r) - bs(v, l - 1); }

  // arr[0 ~ i]范围上
  // (<v的数) + (==v但下标<=i的数)，有几个
  int bs(int v, int i)
  {
    int left = 0, right = n - 1, mid;
    int find = -1;
    while (left <= right)
    {
      mid = (left + right) >> 1;
      if (nums[mid][0] < v || (nums[mid][0] == v && nums[mid][1] <= i))
      {
        find = mid;
        left = mid + 1;
      }
      else
      {
        right = mid - 1;
      }
    }
    return find + 1;
  }

  void up(int i)
  {
    int lc = cand[i << 1], lh = hp[i << 1];
    int rc = cand[i << 1 | 1], rh = hp[i << 1 | 1];
    cand[i] = lc == rc || lh >= rh ? lc : rc;
    hp[i] = lc == rc ? (lh + rh) : std::abs(lh - rh);
  }

  void buildTree(vector<int>& arr, int l, int r, int i)
  {
    if (l == r)
    {
      cand[i] = arr[l - 1];
      hp[i] = 1;
    }
    else
    {
      int mid = (l + r) >> 1;
      buildTree(arr, l, mid, i << 1);
      buildTree(arr, mid + 1, r, i << 1 | 1);
      up(i);
    }
  }

  vector<int> findCandidate(int jobl, int jobr, int l, int r, int i)
  {
    if (jobl <= l && r <= jobr)
    {
      return {cand[i], hp[i]};
    }
    else
    {
      int mid = (l + r) >> 1;
      if (jobr <= mid)
      {
        return findCandidate(jobl, jobr, l, mid, i << 1);
      }
      if (jobl > mid)
      {
        return findCandidate(jobl, jobr, mid + 1, r, i << 1 | 1);
      }
      vector<int> lch = findCandidate(jobl, jobr, l, mid, i << 1);
      vector<int> rch = findCandidate(jobl, jobr, mid + 1, r, i << 1 | 1);
      int lc = lch[0], lh = lch[1];
      int rc = rch[0], rh = rch[1];
      int c = lc == rc || lh >= rh ? lc : rc;
      int h = lc == rc ? (lh + rh) : std::abs(lh - rh);
      return {c, h};
    }
  }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
