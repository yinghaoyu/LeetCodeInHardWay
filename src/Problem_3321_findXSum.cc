#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// @sa https://leetcode.cn/problems/find-x-sum-of-all-k-long-subarrays-ii/
// @sa Problem_3318_findXSum.cc
class Solution
{
 public:
  vector<long long> findXSum(vector<int>& nums, int k, int x)
  {
    // 出现次数，元素值
    using pii = pair<int, int>;
    set<pii> L, R;
    // L的元素和
    long long sum_l = 0;
    // 元素值，出现次数
    unordered_map<int, int> cnt;

    auto add = [&](int x)
    {
      pii p = {cnt[x], x};
      if (p.first == 0)
      {
        return;
      }
      if (!L.empty() && p > *L.begin())
      {
        // p 比 L 中最小的还大
        sum_l += (long long) p.first * p.second;
        L.insert(p);
      }
      else
      {
        R.insert(p);
      }
    };

    auto del = [&](int x)
    {
      pii p = {cnt[x], x};
      if (p.first == 0)
      {
        return;
      }
      auto it = L.find(p);
      if (it != L.end())
      {
        sum_l -= (long long) p.first * p.second;
        L.erase(it);
      }
      else
      {
        R.erase(p);
      }
    };

    // L元素移动到R
    auto l2r = [&]()
    {
      pii p = *L.begin();
      sum_l -= (long long) p.first * p.second;
      L.erase(p);
      R.insert(p);
    };

    // R元素移动到L
    auto r2l = [&]()
    {
      pii p = *R.rbegin();
      sum_l += (long long) p.first * p.second;
      R.erase(p);
      L.insert(p);
    };

    vector<long long> ans(nums.size() - k + 1);
    for (int r = 0; r < nums.size(); r++)
    {
      // 添加 in
      int in = nums[r];
      del(in);
      cnt[in]++;
      add(in);

      int l = r + 1 - k;
      if (l < 0)
      {
        // 窗口还没满，不需要淘汰元素
        continue;
      }

      // 维护大小
      while (!R.empty() && L.size() < x)
      {
        r2l();
      }
      while (L.size() > x)
      {
        l2r();
      }
      ans[l] = sum_l;

      // 移除 out
      int out = nums[l];
      del(out);
      cnt[out]--;
      add(out);
    }
    return ans;
  }
};
