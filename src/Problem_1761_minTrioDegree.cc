#include <cstdint>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int minTrioDegree(int n, vector<vector<int>> &edges)
  {
    vector<vector<int>> g(n, vector<int>(n));
    vector<int> degree(n);
    for (int i = 0; i < edges.size(); i++)
    {
      int x = edges[i][0] - 1;
      int y = edges[i][1] - 1;
      g[x][y] = 1;
      g[y][x] = 1;
      degree[x]++;
      degree[y]++;
    }
    int ans = INT32_MAX;
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        if (g[i][j] == 1)
        {
          for (int k = j + 1; k < n; k++)
          {
            if (g[i][k] == 1 && g[j][k] == 1)
            {
              ans = std::min(ans, degree[i] + degree[j] + degree[k] - 6);
            }
          }
        }
      }
    }
    return ans == INT32_MAX ? -1 : ans;
  }
};

void test()
{
  Solution s;
  vector<vector<int>> e1 = {{1, 2}, {1, 3}, {3, 2}, {4, 1}, {5, 2}, {3, 6}};
  vector<vector<int>> e2 = {{1, 3}, {4, 1}, {4, 3}, {2, 5}, {5, 6}, {6, 7}, {7, 5}, {2, 6}};
  EXPECT_EQ_INT(3, s.minTrioDegree(6, e1));
  EXPECT_EQ_INT(0, s.minTrioDegree(7, e2));
  EXPECT_SUMMARY;
}

int main()
{
  test();
  return 0;
}
