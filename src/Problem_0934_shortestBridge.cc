#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int shortestBridge(vector<vector<int>> &grid)
  {
    int N = grid.size();
    int M = grid[0].size();
    int all = N * M;
    int island = 0;
    vector<int> curs(all);
    vector<int> nexts(all);
    vector<vector<int>> records(2, vector<int>(all));
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < M; j++)
      {
        if (grid[i][j] == 1)
        {
          // 当前位置发现了1！
          // 把这一片的1，都变成2，同时，抓上来了，这一片1组成的初始队列
          // curs, 把这一片的1到自己的距离，都设置成1了，records
          int queueSize = infect(grid, i, j, M, N, curs, 0, records[island]);
          int V = 1;
          while (queueSize != 0)
          {
            V++;
            queueSize = bfs(N, M, all, V, curs, queueSize, nexts, records[island]);
            vector<int> tmp = curs;
            curs = nexts;
            nexts = tmp;
          }
          island++;  // island 只有 0 和 1
        }
      }
    }
    int min = INT32_MAX;
    for (int i = 0; i < all; i++)
    {
      // 比如，
      // 第一次外圈往内bfs
      // 1 1 1 1 1         1 1 1 1 1
      // 1 0 0 0 1         1 2 2 2 1
      // 1 0 1 0 1   -->   1 2 3 2 1
      // 1 0 0 0 1         1 2 2 2 1
      // 1 1 1 1 1         1 1 1 1 1
      // 第二次内圈往外bfs
      // 1 1 1 1 1         3 3 3 3 3
      // 1 0 0 0 1         3 2 2 2 3
      // 1 0 1 0 1   -->   3 2 1 2 3
      // 1 0 0 0 1         3 2 2 2 3
      // 1 1 1 1 1         3 3 3 3 3
      min = std::min(min, records[0][i] + records[1][i]);
    }
    // 由于代价从1开始，同时重复计算了相遇节点1次，因此需要-3
    return min - 3;
  }

  // dfs
  // 当前来到m[i][j] , 总行数是N，总列数是M
  // m[i][j]感染出去(找到这一片岛所有的1),把每一个1的坐标，放入到int[] curs队列！
  // 1 (a,b) -> curs[index++] = (a * M + b)
  // 1 (c,d) -> curs[index++] = (c * M + d)
  // 二维已经变成一维了， 1 (a,b) -> a * M + b
  // 设置距离record[a * M +b ] = 1
  int infect(vector<vector<int>> &m, int i, int j, int N, int M, vector<int> &curs, int index, vector<int> &record)
  {
    if (i < 0 || i == N || j < 0 || j == M || m[i][j] != 1)
    {
      return index;
    }
    // m[i][j] 不越界，且m[i][j] == 1
    m[i][j] = 2;
    int p = i * M + j;
    record[p] = 1;
    // 收集到不同的1
    curs[index++] = p;
    index = infect(m, i - 1, j, N, M, curs, index, record);
    index = infect(m, i + 1, j, N, M, curs, index, record);
    index = infect(m, i, j - 1, N, M, curs, index, record);
    index = infect(m, i, j + 1, N, M, curs, index, record);
    return index;
  }

  // 二维原始矩阵中，N总行数，M总列数
  // all 总 all = N * M
  // V 要生成的是第几层 curs V-1 nexts V
  // record里面拿距离
  int bfs(int N, int M, int all, int V, vector<int> &curs, int size, vector<int> &nexts, vector<int> &record)
  {
    int nexti = 0;  // 我要生成的下一层队列成长到哪了？
    for (int i = 0; i < size; i++)
    {
      // curs[i] -> 一个位置
      // 往4个方向扩散
      int up = curs[i] < M ? -1 : curs[i] - M;
      int down = curs[i] + M >= all ? -1 : curs[i] + M;
      int left = curs[i] % M == 0 ? -1 : curs[i] - 1;
      int right = curs[i] % M == M - 1 ? -1 : curs[i] + 1;
      if (up != -1 && record[up] == 0)
      {
        record[up] = V;
        nexts[nexti++] = up;
      }
      if (down != -1 && record[down] == 0)
      {
        record[down] = V;
        nexts[nexti++] = down;
      }
      if (left != -1 && record[left] == 0)
      {
        record[left] = V;
        nexts[nexti++] = left;
      }
      if (right != -1 && record[right] == 0)
      {
        record[right] = V;
        nexts[nexti++] = right;
      }
    }
    return nexti;
  }
};

void testShortestBridge()
{
  Solution s;
  vector<vector<int>> m1 = {{0, 1}, {1, 0}};
  vector<vector<int>> m2 = {{0, 1, 0}, {0, 0, 0}, {0, 0, 1}};
  vector<vector<int>> m3 = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
  EXPECT_EQ_INT(1, s.shortestBridge(m1));
  EXPECT_EQ_INT(2, s.shortestBridge(m2));
  EXPECT_EQ_INT(1, s.shortestBridge(m3));
  EXPECT_SUMMARY;
}

int main()
{
  testShortestBridge();
  return 0;
}
