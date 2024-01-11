#include <vector>
#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  // 用数组表示路径实现的N皇后问题，不推荐
  int totalNQueens1(int n)
  {
    if (n < 1)
    {
      return 0;
    }
    vector<int> arr(n);
    return f1(0, arr, n);
  }

  // i : 当前来到的行
  // path : 0...i-1行的皇后，都摆在了哪些列
  // n : 是几皇后问题
  // 返回 : 0...i-1行已经摆完了，i....n-1行可以去尝试的情况下还能找到几种有效的方法
  int f1(int i, vector<int>& path, int n)
  {
    if (i == n)
    {
      return 1;
    }
    int ans = 0;
    // 每一行都可以在 n 列上尝试
    for (int j = 0; j < n; j++)
    {
      if (check(path, i, j))
      {
        path[i] = j;
        ans += f1(i + 1, path, n);
      }
    }
    return ans;
  }

  // 当前在i行、j列的位置，摆了一个皇后
  // 0...i-1行的皇后状况，path[0...i-1]
  // 返回会不会冲突，不会冲突，有效！true
  // 会冲突，无效，返回false
  bool check(vector<int>& path, int i, int j)
  {
    for (int k = 0; k < i; k++)
    {
      if (j == path[k] || std::abs(i - k) == std::abs(j - path[k]))
      {
        // 1. 前面位置的列跟当前的列在同一列
        // 2. 前面位置跟当前位置在同意对角线
        return false;
      }
    }
    return true;
  }

  // 当 n < 32 时，空间优化，位信息替代数组
  int totalNQueens2(int n)
  {
    if (n < 1)
    {
      return 0;
    }
    // n = 5
    // 1 << 5 = 0...100000 - 1
    // limit  = 0...011111;
    // n = 7
    // limit  = 0...01111111;
    int limit = (1 << n) - 1;
    return f2(limit, 0, 0, 0);
  }

  // limit : 当前是几皇后问题
  // 之前皇后的列影响：col
  // 之前皇后的右上 -> 左下对角线影响：left
  // 之前皇后的左上 -> 右下对角线影响：right
  int f2(int limit, int col, int left, int right)
  {
    if (col == limit)
    {
      // 所有皇后放完了！
      return 1;
    }
    // 总限制
    int ban = col | left | right;
    // ~ban : 1可放皇后，0不能放
    int candidate = limit & (~ban);
    // 放置皇后的尝试！
    int place = 0;
    // 一共有多少有效的方法
    int ans = 0;
    while (candidate != 0)
    {
      // 提取出最右侧的1
      // 0 0 1 1 1 0
      // 5 4 3 2 1 0
      // place :
      // 0 0 0 0 1 0
      // candidate :
      // 0 0 1 1 0 0
      // 5 4 3 2 1 0
      // place :
      // 0 0 0 1 0 0
      // candidate :
      // 0 0 1 0 0 0
      // 5 4 3 2 1 0
      // place :
      // 0 0 1 0 0 0
      // candidate :
      // 0 0 0 0 0 0
      // 5 4 3 2 1 0
      place = candidate & (-candidate);
      candidate ^= place;
      ans += f2(limit, col | place, (left | place) >> 1, (right | place) << 1);
    }
    return ans;
  }
};

void test()
{
  Solution s;
  EXPECT_EQ_INT(2, s.totalNQueens1(4));
  EXPECT_EQ_INT(1, s.totalNQueens1(1));
  EXPECT_EQ_INT(2, s.totalNQueens2(4));
  EXPECT_EQ_INT(1, s.totalNQueens2(1));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
