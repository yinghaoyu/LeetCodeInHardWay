#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "UnitTest.h"

using namespace std;

class Solution
{
 public:
  int maxPoints(vector<vector<int>> &points)
  {
    if (points.size() <= 2)
    {
      return points.size();
    }
    // Map<string, int>   "3_5"   6
    // 3 / 5    4
    // 3 / 7    10
    // 3 / 17   11
    // 5 / 7    9
    // 5 / 9    3
    // 3 :    (  5 , 4    7, 10,      17 ,  11      )
    // 5 :    (  7 , 9    9, 3  )
    unordered_map<int, unordered_map<int, int>> map;
    int result = 0;
    for (int i = 0; i < points.size(); i++)
    {
      map.clear();
      int samePosition = 1;
      int sameX = 0;
      int sameY = 0;
      int line = 0;  // 哪个斜率压中的点最多，把最多的点的数量，赋值给line
      for (int j = i + 1; j < points.size(); j++)
      {
        int x = points[j][0] - points[i][0];
        int y = points[j][1] - points[i][1];
        if (x == 0 && y == 0)
        {
          samePosition++;
        }
        else if (x == 0)
        {
          sameX++;
        }
        else if (y == 0)
        {
          sameY++;
        }
        else
        {  // 有斜率
          int g = gcd(x, y);
          x /= g;
          y /= g;
          if (!map.count(x))
          {
            map.emplace(x, unordered_map<int, int>());
          }
          if (!map.at(x).count(y))
          {
            map.at(x).emplace(y, 0);
          }
          map.at(x).at(y)++;
          line = std::max(line, map.at(x).at(y));
        }
      }
      result = std::max(result, std::max(std::max(sameX, sameY), line) + samePosition);
    }
    return result;
  }

  // 保证初始调用的时候，a和b不等于0
  // O(1)
  int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
};

void testMaxPoints()
{
  Solution s;
  vector<vector<int>> p1 = {{1, 1}, {2, 2}, {3, 3}};
  vector<vector<int>> p2 = {{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}};
  EXPECT_EQ_INT(3, s.maxPoints(p1));
  EXPECT_EQ_INT(4, s.maxPoints(p2));
  EXPECT_SUMMARY;
}

int main()
{
  testMaxPoints();
  return 0;
}
