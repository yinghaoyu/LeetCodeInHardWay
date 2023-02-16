#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;
class Solution
{
 public:
  // 时间复杂度Log(N^2)
  int largestRectangleArea1(vector<int> &heights)
  {
    int ans = 0;
    for (int i = 0; i < heights.size(); i++)
    {
      int l = i;
      int cur = heights[i];
      while (l > 0 && heights[l - 1] >= cur)
      {
        // 找左边最后 1 个 >= heights[i] 的下标
        l--;
      }
      int r = i;
      while (r < heights.size() - 1 && heights[r + 1] >= cur)
      {
        // 找右边最后 1 个 >= heights[i] 的下标
        r++;
      }
      int w = r - l + 1;
      ans = std::max(ans, w * cur);
    }
    return ans;
  }

  // https://leetcode.cn/problems/largest-rectangle-in-histogram/solution/bao-li-jie-fa-zhan-by-liweiwei1419/
  // 利用单调栈优化
  int largestRectangleArea2(vector<int> &heights)
  {
    if (heights.size() == 0)
    {
      return 0;
    }
    int maxArea = 0;
    vector<int> stack;
    for (int i = 0; i < heights.size(); i++)
    {
      // 单调递增栈
      while (!stack.empty() && heights[i] <= heights[stack.back()])
      {
        int j = stack.back();
        stack.pop_back();
        int k = stack.empty() ? -1 : stack.back();
        int curArea = (i - k - 1) * heights[j];
        maxArea = std::max(maxArea, curArea);
      }
      stack.push_back(i);
    }
    while (!stack.empty())
    {
      int j = stack.back();
      stack.pop_back();
      int k = stack.empty() ? -1 : stack.back();
      int curArea = (heights.size() - k - 1) * heights[j];
      maxArea = std::max(maxArea, curArea);
    }
    return maxArea;
  }
};

void testLargestRectangleArea()
{
  Solution s;
  vector<int> h1 = {2, 1, 5, 6, 2, 3};
  vector<int> h2 = {2, 4};
  EXPECT_EQ_INT(10, s.largestRectangleArea2(h1));
  EXPECT_EQ_INT(4, s.largestRectangleArea2(h2));
  EXPECT_SUMMARY;
}

int main()
{
  testLargestRectangleArea();
  return 0;
}
