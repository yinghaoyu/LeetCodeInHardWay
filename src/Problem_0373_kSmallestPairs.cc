#include <iostream>
#include <queue>
#include <vector>

#include "UnitTest.h"

using namespace std;

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

void test()
{
  Solution s;
  vector<int> n1 = {1, 7, 11};
  vector<int> n2 = {2, 4, 6};
  vector<int> n3 = {1, 1, 2};
  vector<int> n4 = {1, 2, 3};
  vector<int> n5 = {1, 2};
  vector<int> n6 = {3};
  vector<vector<int>> o1 = {{1, 2}, {1, 4}, {1, 6}};
  vector<vector<int>> o2 = {{1, 1}, {1, 1}};
  vector<vector<int>> o3 = {{1, 3}, {2, 3}};
  auto x = s.kSmallestPairs(n1, n2, 3);
  auto y = s.kSmallestPairs(n3, n4, 2);
  auto z = s.kSmallestPairs(n5, n6, 3);
  EXPECT_TRUE(o1 == x);
  EXPECT_TRUE(o2 == y);
  EXPECT_TRUE(o3 == z);
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
