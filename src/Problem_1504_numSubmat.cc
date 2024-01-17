#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int numSubmat(vector<vector<int>>& mat)
  {
    if (mat.size() == 0 || mat[0].size() == 0)
    {
      return 0;
    }
    int nums = 0;
    vector<int> height(mat[0].size());
    for (int i = 0; i < mat.size(); i++)
    {
      for (int j = 0; j < mat[0].size(); j++)
      {
        height[j] = mat[i][j] == 0 ? 0 : height[j] + 1;
      }
      nums += countFromBottom(height);
    }
    return nums;
  }

  int countFromBottom(vector<int> height)
  {
    if (height.size() == 0)
    {
      return 0;
    }
    int nums = 0;
    vector<int> stack(height.size());
    int si = -1;
    for (int i = 0; i < height.size(); i++)
    {
      // 构建单调递增栈，不符合时弹出结算
      while (si != -1 && height[stack[si]] >= height[i])
      {
        // height[cur] 是区间 [left, i)之间的最小值
        int cur = stack[si--];
        if (height[cur] > height[i])  // 相等的时候舍弃，不然会重复计算
        {
          int left = si == -1 ? -1 : stack[si];
          // 形成直方图宽度n
          int n = i - left - 1;
          int down = std::max(left == -1 ? 0 : height[left], height[i]);
          // 形成的直方图有效结算高度height[cur] - down
          // l = left，c = cur
          // 计算必须以最后一行为底，且一定包含♠的矩阵
          //      _                _                _                 _
          //    _|♠|             _|*|             _|*|              _|*|
          //   |*|*|_           |♠|♠|_           |*|*|_            |*|*|_
          //  _|*|*|*|         _|*|*|*|         _|♠|♠|♠|          _|*|*|*|
          // |*|*|*|*|   -->  |*|*|*|*|   -->  |*|*|*|*|    -->  |♠|♠|♠|♠|
          // |*|*|*|*|        |*|*|*|*|        |*|*|*|*|         |♠|♠|♠|♠|
          //  ↑   ↑ ↑          ↑ ↑   ↑          ↑     ↑           ↑
          //  l   c i          l c   i          l     c           c
          nums += (height[cur] - down) * num(n);
        }
      }
      stack[++si] = i;
    }
    while (si != -1)
    {
      int cur = stack[si--];
      int left = si == -1 ? -1 : stack[si];
      int n = height.size() - left - 1;
      int down = left == -1 ? 0 : height[left];
      nums += (height[cur] - down) * num(n);
    }
    return nums;
  }

  int num(int n) { return ((n * (1 + n)) >> 1); }
};

void test()
{
  Solution s;
  vector<vector<int>> m1 = {{1, 0, 1}, {1, 1, 0}, {1, 1, 0}};
  vector<vector<int>> m2 = {{0, 1, 1, 0}, {0, 1, 1, 1}, {1, 1, 1, 0}};
  EXPECT_EQ_INT(13, s.numSubmat(m1));
  EXPECT_EQ_INT(24, s.numSubmat(m2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
