#include <iostream>
#include <iterator>
#include <vector>

#include "UnitTest.h"

using namespace std;

// 二维前缀和 + 二维差分
class Solution
{
 public:
  bool possibleToStamp(vector<vector<int>> &grid, int stampHeight, int stampWidth)
  {
    int N = grid.size();
    int M = grid[0].size();
    // 左上角累加和数组
    // 快速查询矩阵中的某块累加和
    vector<vector<int>> sum(N + 1, vector<int>(M + 1));
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        sum[i + 1][j + 1] = grid[i][j];
      }
    }
    build(sum);
    // 差分矩阵
    // 当贴邮票时，在差分矩阵贴
    vector<vector<int>> diff(N + 2, vector<int>(M + 2));
    for (int a = 1, c = a + stampHeight - 1; c <= N; a++, c++)
    {
      for (int b = 1, d = b + stampWidth - 1; d <= M; b++, d++)
      {
        // (a, b) (c, d)
        if (empty(sum, a, b, c, d))
        {
          set(diff, a, b, c, d);
        }
      }
    }
    build(diff);
    // 检查所有格子
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        if (grid[i][j] == 0 && diff[i + 1][j + 1] == 0)
        {
          return false;
        }
      }
    }
    return true;
  }

  void build(vector<vector<int>> &arr)
  {
    int N = arr.size();
    int M = arr[0].size();
    for (int i = 1; i < N; i++)
    {
      for (int j = 1; j < M; j++)
      {
        arr[i][j] += arr[i - 1][j] + arr[i][j - 1] - arr[i - 1][j - 1];
      }
    }
  }

  bool empty(vector<vector<int>> &arr, int a, int b, int c, int d) { return arr[c][d] - arr[c][b - 1] - arr[a - 1][d] + arr[a - 1][b - 1] == 0; }

  void set(vector<vector<int>> &arr, int a, int b, int c, int d)
  {
    arr[a][b] += 1;
    arr[c + 1][d + 1] += 1;
    arr[c + 1][b] -= 1;
    arr[a][d + 1] -= 1;
  }
};

void testPossibleToStamp()
{
  Solution s;
  vector<vector<int>> g1 = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};
  vector<vector<int>> g2 = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};
  EXPECT_TRUE(s.possibleToStamp(g1, 4, 3));
  EXPECT_FALSE(s.possibleToStamp(g2, 2, 2));
  EXPECT_SUMMARY;
}

int main()
{
  testPossibleToStamp();
  return 0;
}
