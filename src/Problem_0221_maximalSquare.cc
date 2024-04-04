#include <algorithm>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 二维单调栈，根据第85题改写
  int maximalSquare1(vector<vector<char>>& matrix)
  {
    int N = matrix.size();
    int M = matrix[0].size();
    vector<int> height(M);
    int ans = 0;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        height[j] = matrix[i][j] == '0' ? 0 : height[j] + 1;
      }
      ans = std::max(ans, maxFromButton(height));
    }
    return ans;
  }

  int maxFromButton(vector<int>& height)
  {
    int ans = 0;
    int N = height.size();
    vector<int> stack;
    for (int i = 0; i < N; i++)
    {
      while (!stack.empty() && height[stack.back()] >= height[i])
      {
        int j = stack.back();
        stack.pop_back();
        // 左边不能扩到的位置
        // (k, j]区间内，所有的值一定是 >= height[j]的
        int k = stack.empty() ? -1 : stack.back();
        // [j, i)区间内，所有的值一定是 >= height[j]的
        int width = i - k - 1;
        if (width >= height[j])
        {
          // 取正方体
          int area = height[j] * height[j];
          ans = std::max(ans, area);
        }
      }
      stack.push_back(i);
    }
    while (!stack.empty())
    {
      int j = stack.back();
      stack.pop_back();
      int k = stack.empty() ? -1 : stack.back();
      int width = N - k - 1;
      if (width >= height[j])
      {
        int area = height[j] * height[j];
        ans = std::max(ans, area);
      }
    }
    return ans;
  }

  // 动态规划
  // 拓展题1 统计全为 1 的正方形子矩阵
  // @sa https://leetcode.cn/problems/count-square-submatrices-with-all-ones/
  // 拓展题2 最大黑方阵 Problem_17.23_findSquare.cc
  // @sa https://leetcode.cn/problems/max-black-square-lcci/
  int maximalSquare2(vector<vector<char>>& matrix)
  {
    if (matrix.size() == 0 || matrix[0].size() == 0)
    {
      return 0;
    }
    int N = matrix.size();
    int M = matrix[0].size();
    // dp[i][j] 是以 matrix[i][j] 为 右下角 的正方形的最大边长
    vector<vector<int>> dp(N, vector<int>(M));
    int max = 0;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        // matrix[i][j] == 0，则dp[i][j] = 0，因为当前位置不可能在由1组成的正方形中
        if (matrix[i][j] == '1')
        {
          if (i == 0 || j == 0)
          {
            //  如果 i 和 j 中至少有一个为 0，则以位置 (i,j) 为右下角的最大正方形的边长只能是 1
            dp[i][j] = 1;
          }
          else
          {
            dp[i][j] = std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
          }
          max = std::max(max, dp[i][j]);
        }
      }
    }
    return max * max;
  }
};

void testMaximalSquare()
{
  Solution s;
  vector<vector<char>> m1 = {{'1', '0', '1', '0', '0'},
                             {'1', '0', '1', '1', '1'},
                             {'1', '1', '1', '1', '1'},
                             {'1', '0', '0', '1', '0'}};
  vector<vector<char>> m2 = {{'0', '1'}, {'1', '0'}};
  vector<vector<char>> m3 = {{'0'}};
  EXPECT_EQ_INT(4, s.maximalSquare1(m1));
  EXPECT_EQ_INT(1, s.maximalSquare1(m2));
  EXPECT_EQ_INT(0, s.maximalSquare1(m3));
  EXPECT_EQ_INT(4, s.maximalSquare2(m1));
  EXPECT_EQ_INT(1, s.maximalSquare2(m2));
  EXPECT_EQ_INT(0, s.maximalSquare2(m3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximalSquare();
  return 0;
}
