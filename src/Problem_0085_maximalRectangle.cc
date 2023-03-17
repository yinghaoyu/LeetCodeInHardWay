#include <iostream>
#include <stack>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 1 0 1 0 0         1  0  1  0  0
// 1 0 1 1 1         1  0 (1  1  1)
// 1 1 1 1 1   -->   1  1 (1  1  1)   answer = 6
// 1 0 0 1 0         1  0  0  1  0
class Solution
{
 public:
  // 第一行
  //  _   _
  // |_|_| |_ _
  //
  // 第二行(第一行传递)
  //  _   _
  // | | | |_ _
  // |_|_|_|_|_|
  //
  // 第三行(第二行传递)
  //  _   _
  // | | | |_ _
  // | |_| | | |
  // |_|_|_|_|_|
  //
  // 第四行(第三行传递)
  //  _
  // | |   _
  // | |  | |
  // | |  | |
  // |_|__|_|__
  int maximalRectangle(vector<vector<char>> &matrix)
  {
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      return 0;
    }
    int N = matrix.size();
    int M = matrix[0].size();
    int maxArea = 0;
    vector<int> height(M);
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        height[j] = matrix[i][j] == '0' ? 0 : height[j] + 1;
      }
      maxArea = std::max(maxArea, maxRecFromBottom(height));
    }
    return maxArea;
  }

  // height是正方图数组
  int maxRecFromBottom(vector<int> &height)
  {
    if (height.size() == 0)
    {
      return 0;
    }
    int maxArea = 0;
    // 左右两侧离最近，小的 ,,,,  底  -> 顶        小   ->  大
    stack<int> stack;
    for (int i = 0; i < height.size(); i++)
    {
      while (!stack.empty() && height[i] <= height[stack.top()])
      {
        int j = stack.top();  // 结算哪个位置的答案
        stack.pop();
        int k = stack.empty() ? -1 : stack.top();  // 左边不能扩到的位置
        int curArea = (i - k - 1) * height[j];
        maxArea = std::max(maxArea, curArea);
      }
      stack.push(i);
    }
    while (!stack.empty())
    {
      int j = stack.top();
      stack.pop();
      int k = stack.empty() ? -1 : stack.top();
      int curArea = (height.size() - k - 1) * height[j];
      maxArea = std::max(maxArea, curArea);
    }
    return maxArea;
  }
};

void testMaximalRectangle()
{
  Solution s;
  vector<vector<char>> m1 = {{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}};
  vector<vector<char>> m2 = {{'0'}};
  EXPECT_EQ_INT(6, s.maximalRectangle(m1));
  EXPECT_EQ_INT(0, s.maximalRectangle(m2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximalRectangle();
  return 0;
}
