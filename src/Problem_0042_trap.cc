#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 动态规划
  int dp(vector<int> &height)
  {
    int n = height.size();
    vector<int> left(n);
    vector<int> right(n);
    left[0] = height[0];
    for (int i = 1; i < n; i++)
    {
      left[i] = std::max(left[i-1], height[i]);
    }
    right[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
      right[i] = std::max(right[i + 1], height[i]);
    }
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      ans += std::min(left[i], right[i]) - height[i];
    }
    return ans;
  }

  // 单调栈
  int trap(vector<int> &height)
  {
    int ans = 0;
    vector<int> stack;
    int n = height.size();
    for (int i = 0; i < n; i++)
    {
      while (!stack.empty() && height[stack.back()] < height[i])
      {
        int x = stack.back();
        stack.pop_back();
        if (stack.empty())
        {
          break;
        }
        int left = stack.back();
        int curWidth = i - left - 1;
        int curHeight = std::min(height[left], height[i]) - height[x];
        ans += curWidth * curHeight;
      }
      stack.push_back(i);
    }
    return ans;
  }
};

void testTrap()
{
  Solution s;
  vector<int> h1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  vector<int> h2 = {4, 2, 0, 3, 2, 5};
  EXPECT_EQ_INT(6, s.trap(h1));
  EXPECT_EQ_INT(9, s.trap(h2));
  EXPECT_EQ_INT(6, s.dp(h1));
  EXPECT_EQ_INT(9, s.dp(h2));
  EXPECT_SUMMARY;
}

int main()
{
  testTrap();
  return 0;
}
