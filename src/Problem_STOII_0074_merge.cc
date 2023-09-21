#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// @sa https://leetcode-cn.com/problems/merge-intervals/
// @sa Problem_0056_merge.cc

class Solution
{
 public:
  vector<vector<int>> merge(vector<vector<int>> &intervals)
  {
    std::sort(intervals.begin(), intervals.end());
    vector<vector<int>> ans;
    for (auto &e : intervals)
    {
      int left = e[0];
      int right = e[1];
      if (ans.empty() || ans.back()[1] < left)
      {
        ans.push_back({left, right});
      }
      else
      {
        ans.back()[1] = std::max(ans.back()[1], right);
      }
    }
    return ans;
  }
};
