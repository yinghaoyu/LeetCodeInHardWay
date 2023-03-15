#include <iostream>
#include <iterator>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maximalNetworkRank(int n, vector<vector<int>> &roads)
  {
    vector<vector<bool>> connect(n, vector<bool>(n));
    vector<int> degree(n);
    for (auto &v : roads)
    {
      connect[v[0]][v[1]] = true;
      connect[v[1]][v[0]] = true;
      degree[v[0]]++;
      degree[v[1]]++;
    }
    int max = 0;
    for (int i = 0; i < n; i++)
    {
      for (int j = i + 1; j < n; j++)
      {
        int rank = degree[i] + degree[j] - (connect[i][j] ? 1 : 0);
        max = std::max(max, rank);
      }
    }
    return max;
  }
};

void testMaximalNetworkRank()
{
  Solution s;
  vector<vector<int>> n1 = {{0, 1}, {0, 3}, {1, 2}, {1, 3}};
  vector<vector<int>> n2 = {{0, 1}, {0, 3}, {1, 2}, {1, 3}, {2, 3}, {2, 4}};
  vector<vector<int>> n3 = {{0, 1}, {1, 2}, {2, 3}, {2, 4}, {5, 6}, {5, 7}};
  EXPECT_EQ_INT(4, s.maximalNetworkRank(4, n1));
  EXPECT_EQ_INT(5, s.maximalNetworkRank(5, n2));
  EXPECT_EQ_INT(5, s.maximalNetworkRank(8, n3));
  EXPECT_SUMMARY;
}

int main()
{
  testMaximalNetworkRank();
  return 0;
}
