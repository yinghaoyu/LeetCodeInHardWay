#include <iostream>
#include <queue>
#include <vector>

using namespace std;

// seem as leetcode 0373
// https://leetcode-cn.com/problems/find-k-pairs-with-smallest-sums/
// see at Problem_0373_kSmallestPairs.cc
class Solution
{
 public:
  vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k)
  {
    auto cmp = [&](pair<int, int> &l, pair<int, int> &r) { return nums1[l.first] + nums2[l.second] > nums1[r.first] + nums2[r.second]; };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> q(cmp);
    int n = nums1.size();
    int m = nums2.size();
    for (int i = 0; i < std::min(k, n); i++)
    {
      q.push({i, 0});
    }
    vector<vector<int>> ans;
    while (k-- > 0 && !q.empty())
    {
      auto [x, y] = q.top();
      q.pop();
      ans.push_back({nums1[x], nums2[y]});
      if (y + 1 < m)
      {
        q.push({x, y + 1});
      }
    }
    return ans;
  }
};
