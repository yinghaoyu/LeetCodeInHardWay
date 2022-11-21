#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int shortestPathAllKeys(vector<string> &grid)
  {
    int n = grid.size();
    int m = grid[0].size();
    int start_x = 0;
    int start_y = 0;
    unordered_map<char, int> keys;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < m; j++)
      {
        if (grid[i][j] == '@')
        {
          // 记录开始坐标
          start_x = i;
          start_y = j;
        }
        else if (std::islower(grid[i][j]))
        {
          if (!keys.count(grid[i][j]))
          {
            // 记录钥匙的索引
            int idx = keys.size();
            keys[grid[i][j]] = idx;
          }
        }
      }
    }
    // bfs的队列
    queue<tuple<int, int, int>> que;
    // 到起点的距离 distance[x][y][k]，x表示横坐标，y表示纵坐标，k的每 1 bit表示获取的锁
    // k = 00001 表示获取了索引为 0 的锁
    vector<vector<vector<int>>> distance(n, vector<vector<int>>(m, vector<int>(1 << keys.size(), -1)));
    que.emplace(start_x, start_y, 0);  // 0表示没有获取钥匙
    distance[start_x][start_y][0] = 0;
    while (!que.empty())
    {
      auto [x, y, mask] = que.front();
      que.pop();
      for (int i = 0; i < 4; i++)
      {
        int next_x = x + directions[i][0];
        int next_y = y + directions[i][1];
        if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < m && grid[next_x][next_y] != '#')
        {
          // 坐标没有越界，并且当前字符不是墙
          if (grid[next_x][next_y] == '.' || grid[next_x][next_y] == '@')
          {
            // 当前字符是正常的通道，或者是开始的点
            if (distance[next_x][next_y][mask] == -1)
            {
              // 为什么判断 == -1
              // 因为广度遍历第一次到达该节点，就是最短路径，所以只取第一次到达的距离
              distance[next_x][next_y][mask] = distance[x][y][mask] + 1;
              que.emplace(next_x, next_y, mask);
            }
          }
          else if (std::islower(grid[next_x][next_y]))
          {
            // 当前字符是钥匙
            int idx = keys[grid[next_x][next_y]];
            if (distance[next_x][next_y][mask | (1 << idx)] == -1)
            {
              distance[next_x][next_y][mask | (1 << idx)] = distance[x][y][mask] + 1;
              if ((mask | (1 << idx)) == (1 << keys.size()) - 1)
              {
                // 获取了所有钥匙，返回结果
                return distance[next_x][next_y][mask | (1 << idx)];
              }
            }
            que.emplace(next_x, next_y, mask | (1 << idx));
          }
          else
          {
            // 当前字符是锁
            int idx = keys[std::tolower(grid[next_x][next_y])];
            if ((mask & (1 << idx)) && distance[next_x][next_y][mask] == -1)
            {
              // mask已经获得过该锁的钥匙
              distance[next_x][next_y][mask] = distance[x][y][mask] + 1;
              que.emplace(next_x, next_y, mask);
            }
          }
        }
      }
    }
    return -1;
  }

 private:
  static constexpr int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
};

void testShortestPathAllKeys()
{
  Solution s;
  vector<string> g1 = {"@.a..", "###.#", "b.A.B"};
  vector<string> g2 = {"@..aA", "..B#.", "....b"};
  vector<string> g3 = {"@Aa"};
  vector<string> g4 = {".@aA"};
  EXPECT_EQ_INT(8, s.shortestPathAllKeys(g1));
  EXPECT_EQ_INT(6, s.shortestPathAllKeys(g2));
  EXPECT_EQ_INT(-1, s.shortestPathAllKeys(g3));
  EXPECT_EQ_INT(1, s.shortestPathAllKeys(g4));
  EXPECT_SUMMARY;
}

int main()
{
  testShortestPathAllKeys();
  return 0;
}
