#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

// @sa
// https://leetcode.cn/problems/volume-of-histogram-lcci/solutions/692343/zhi-fang-tu-de-shui-liang-by-leetcode-so-7rla/
class Solution
{
 public:
  // 动态规划
  int trap1(vector<int>& height)
  {
    int n = height.size();
    if (n == 0)
    {
      return 0;
    }
    // leftMax[i] 表示左边最高的柱子
    vector<int> leftMax(n);
    leftMax[0] = height[0];
    for (int i = 1; i < n; i++)
    {
      leftMax[i] = std::max(leftMax[i - 1], height[i]);
    }
    // rightMax[i] 表示右边最高的柱子
    vector<int> rightMax(n);
    rightMax[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
      rightMax[i] = std::max(rightMax[i + 1], height[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
    {
      ans += std::min(leftMax[i], rightMax[i]) - height[i];
    }
    return ans;
  }

  // 单调栈
  int trap2(vector<int>& height)
  {
    int ans = 0;
    stack<int> st;
    int n = height.size();
    for (int i = 0; i < n; i++)
    {
      while (!st.empty() && height[i] > height[st.top()])
      {
        int top = st.top();
        st.pop();
        if (st.empty())
        {
          break;
        }
        int left = st.top();
        int curWidth = i - left - 1;
        int curHeight = std::min(height[left], height[i]) - height[top];
        ans += curWidth * curHeight;
      }
      st.push(i);
    }
    return ans;
  }

  // 动态规划解法启发，双指针
  int trap3(vector<int>& height)
  {
    int ans = 0;
    int left = 0;
    int right = height.size() - 1;
    int leftMax = 0;
    int rightMax = 0;
    while (left < right)
    {
      leftMax = std::max(leftMax, height[left]);
      rightMax = std::max(rightMax, height[right]);
      if (height[left] < height[right])
      {
        // height[left] < height[right]
        // 那么height[left]的水受左侧最大值影响
        ans += leftMax - height[left];
        ++left;
      }
      else
      {
        // height[left] >= height[right]
        // 那么height[right]的水受右侧侧最大值影响
        ans += rightMax - height[right];
        --right;
      }
    }
    return ans;
  }
};
