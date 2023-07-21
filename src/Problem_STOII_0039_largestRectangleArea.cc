#include <iostream>
#include <vector>

using namespace std;

// seem as leetcode 0084
// https://leetcode-cn.com/problems/largest-rectangle-in-histogram/
// see at Problem_0084_largestRectangleArea.cc
class Solution
{
 public:
  int largestRectangleArea(vector<int> &heights)
  {
    vector<int> stack;
    int n = heights.size();
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && heights[stack.back()] >= heights[i])
      {
        // 由于是单调递增栈， (k, j)区间和(j, i) 之间的柱子都高于 i 的柱子
        int j = stack.back();
        stack.pop_back();
        int k = stack.empty() ? -1 : stack.back();
        int curArea = (i - k - 1) * heights[j];
        ans = std::max(ans, curArea);
      }
      stack.push_back(i);
    }
    while (!stack.empty())
    {
      int j = stack.back();
      stack.pop_back();
      int k = stack.empty() ? -1 : stack.back();
      int curArea = (n - k - 1) * heights[j];
      ans = std::max(ans, curArea);
    }
    return ans;
  }
};
