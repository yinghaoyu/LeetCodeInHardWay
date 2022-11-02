#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  vector<int> bestCoordinate(vector<vector<int>> &towers, int radius)
  {
    int n = INT32_MIN;
    int m = INT32_MIN;
    for (auto &&tower : towers)
    {
      n = std::max(n, tower[0]);
      m = std::max(m, tower[1]);
    }
    int x = 0;
    int y = 0;
    int max = 0;
    for (int i = 0; i <= n; i++)  // 先遍历x坐标
    {
      for (int j = 0; j <= m; j++)  // 再遍历y坐标，这样保证了字典序
      {
        vector<int> coordinate = {i, j};
        int sum = 0;
        for (auto &&tower : towers)
        {
          int s = getDistance(coordinate, tower);
          if (s <= radius * radius)
          {
            double distance = sqrt((double) s);
            sum += floor((double) tower[2] / (1 + distance));  // floor 向下取整
          }
        }
        if (sum > max)
        {
          x = i;
          y = j;
          max = sum;
        }
      }
    }
    return {x, y};
  }

  int getDistance(const vector<int> &coordinate, const vector<int> &tower)
  {
    return (tower[0] - coordinate[0]) * (tower[0] - coordinate[0]) + (tower[1] - coordinate[1]) * (tower[1] - coordinate[1]);
  }
};

bool isVectorEqual(vector<int> a, vector<int> b)
{
  if (a.size() != b.size())
  {
    return false;
  }
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] != b[i])
    {
      return false;
    }
  }
  return true;
}

void testBestCoordinate()
{
  Solution s;
  vector<vector<int>> n1 = {{1, 2, 5}, {2, 1, 7}, {3, 1, 9}};
  vector<vector<int>> n2 = {{23, 11, 21}};
  vector<vector<int>> n3 = {{1, 2, 13}, {2, 1, 7}, {0, 1, 9}};
  vector<int> o1 = {2, 1};
  vector<int> o2 = {23, 11};
  vector<int> o3 = {1, 2};
  EXPECT_TRUE(isVectorEqual(o1, s.bestCoordinate(n1, 2)));
  EXPECT_TRUE(isVectorEqual(o2, s.bestCoordinate(n2, 9)));
  EXPECT_TRUE(isVectorEqual(o3, s.bestCoordinate(n3, 2)));
  EXPECT_SUMMARY;
}

int main()
{
  testBestCoordinate();
  return 0;
}
